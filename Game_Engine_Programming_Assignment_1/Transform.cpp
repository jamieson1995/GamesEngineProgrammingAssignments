#include "Transform.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "GameObject.h"
#include "Debug.h"

namespace jutiny
{

	namespace engine
	{

		Transform::~Transform()
		{

		}

		void Transform::onAwake()
		{
			parent = NULL;
			m_localScale = Vector3(1, 1, 1);
		}

		void Transform::onDestroy()
		{
			detachChildren();
			setParent(NULL);
		}

		void Transform::setLocalRotation(Vector3 _rotation)
		{
			m_localRotation = _rotation;
		}

		void Transform::setLocalPosition(Vector3 _position)
		{
			// Take off parent's existing position. Use setLocalPosition to set directly.
			m_localPosition = _position;
		}

		void Transform::setLocalScale(Vector3 _scale)
		{
			m_localScale = _scale;
		}

		Vector3 Transform::getLocalPosition()
		{
			return m_localPosition;
		}

		Vector3 Transform::getLocalRotation()
		{
			return m_localRotation;
		}

		void Transform::setRotation(Vector3 _rotation)
		{
			if (getParent().valid())
			{
				m_localRotation = _rotation - getParent()->getRotation();
			}
			else
			{
				m_localRotation = _rotation;
			}
		}

		void Transform::setPosition(Vector3 _position)
		{
			if (getParent().valid())
			{
				Matrix4x4 trs = Matrix4x4::getIdentity();
				ref<Transform> trans = getParent();

				while (trans.valid())
				{
					trs = Matrix4x4::getTrs(trans->m_localPosition, trans->m_localRotation, Vector3(1, 1, 1)) * trs;
					trans = trans->getParent();
				}

				m_localPosition = trs.inverse() * _position;
			}
			else
			{
				m_localPosition = _position;
			}
		}

		void Transform::setScale(Vector3 _scale)
		{
			if (getParent().valid())
			{
				Matrix4x4 trs = Matrix4x4::getIdentity();
				ref<Transform> trans = getParent();

				while (trans.valid())
				{
					trs = Matrix4x4::getTrs(trans->m_localPosition, trans->m_localRotation, trans->m_localScale) * trs;
					trans = trans->getParent();
				}

				m_localScale = trs.inverse() * _scale;
			}
			else
			{
				m_localScale = _scale;
			}
		}

		Vector3 Transform::getPosition()
		{
			Matrix4x4 trs = Matrix4x4::getIdentity();
			ref<Transform> trans = this;

			while (trans.valid())
			{
				trs = Matrix4x4::getTrs(trans->m_localPosition, trans->m_localRotation, Vector3(1, 1, 1)) * trs;
				trans = trans->getParent();
			}

			return trs * Vector3();
		}

		Vector3 Transform::getRotation()
		{
			ref<Transform> trans = this;
			Vector3 rotation;

			while (trans.valid())
			{
				rotation = rotation + trans->m_localRotation;
				trans = trans->getParent();
			}

			return rotation;
		}

		Vector3 Transform::getScale()
		{
			return m_localScale;
		}

		void Transform::detachChildren()
		{
			while (children.size() > 0)
			{
				ref<Transform> child = children.at(0);
				child->setParent(NULL); //Become BATMAN
				Object::destroy(child->getGameObject());
			}

			children.clear();
		}

		ref<Transform> Transform::find(std::string _name)
		{
			for (int i = 0; i < children.size(); i++)
			{
				if (children.at(i)->getGameObject()->getName() == _name)
				{
					return children.at(i);
				}
			}

			return NULL;
		}

		ref<Transform> Transform::getParent()
		{
			return parent;
		}

		void Transform::setParent(ref<Transform> _transform)
		{
			if (this->parent.valid())
			{
				for (int i = 0; i < this->parent->children.size(); i++)
				{
					if (this->parent->children.at(i).get() == this)
					{
						this->parent->children.erase(this->parent->children.begin() + i);
						break;
					}
				}
			}

			if (_transform.valid())
			{
				_transform->children.push_back(this);
			}

			setLocalPosition(getPosition());
			setLocalRotation(getRotation());
			this->parent = _transform;
			setPosition(getLocalPosition());
			setRotation(getLocalRotation());
		}

		int Transform::getChildCount()
		{
			return children.size();
		}

		ref<Transform> Transform::getChild(int _index)
		{
			return children.at(_index);
		}

		ref<Transform> Transform::getRoot()
		{
			ref<Transform> root = this;
			ref<Transform> trans = parent;

			while (trans.valid())
			{
				root = trans;
				trans = trans->getParent();
			}

			return root;
		}

		void Transform::rotate(Vector3 _eulerAngles)
		{
			m_localRotation.x += _eulerAngles.x;
			m_localRotation.y += _eulerAngles.y;
			m_localRotation.z += _eulerAngles.z;
		}

		void Transform::translate(Vector3 _translation)
		{
			m_localPosition.x += _translation.x;
			m_localPosition.y += _translation.y;
			m_localPosition.z += _translation.z;
		}

		void Transform::lookAt(Vector3 _worldPosition)
		{

			Vector2 diff2 = Vector2(m_localPosition.x, m_localPosition.z) - Vector2(_worldPosition.x, _worldPosition.z);

			float angle = atan2(diff2.x, diff2.y) * 180 / 3.14159265359f;
			m_localRotation.y = angle - 180.0f;
		}

		void Transform::rotateAround(Vector3 _center, Vector3 _axis, float _amount)
		{
			Matrix4x4 pos = Matrix4x4::getTrs(_center,
				Vector3(0, 0, 0), Vector3(1, 1, 1));

			Matrix4x4 rot = Matrix4x4::getTrs(Vector3(0, 0, 0),
				Vector3(_axis * _amount), Vector3(1, 1, 1));

			Matrix4x4 curr = Matrix4x4::getIdentity();
			curr = curr * pos;
			curr = curr * rot;
			curr = curr * pos.inverse();

			m_localPosition = curr * m_localPosition;
		}

		Vector3 Transform::getForward()
		{
			Matrix4x4 m = Matrix4x4::getTrs(m_localPosition, m_localRotation, Vector3(1, 1, 1));

			return m.multiplyVector(Vector3(0, 0, 1));
		}

		Vector3 Transform::getRight()
		{
			Matrix4x4 m = Matrix4x4::getTrs(m_localPosition, m_localRotation, Vector3(1, 1, 1));

			return m.multiplyVector(Vector3(1, 0, 0));
		}
}

}