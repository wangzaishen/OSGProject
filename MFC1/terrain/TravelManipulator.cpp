#include "StdAfx.h"
#include "TravelManipulator.h"


TravelManipulator::TravelManipulator(void):m_fMoveSpeed(1.0f),
	m_bLeftButtonDown(false),
	m_fpushX(0),
	m_fAngle(2.5),
	m_bPeng(true),
	m_fpushY(0)
{
	m_vPosition = osg::Vec3(-22.0f, -274.0f, 100.0f);
	m_vRotation = osg::Vec3(osg::PI_2, 0.0f, 0.0f);
	angle1 = 0;
	angle = 0;
	move = 1;
	scale = 1;
	singal = 0;
	m_fMouseX = 0.0f;
	m_fMouseY = 0.0f;
}


TravelManipulator::~TravelManipulator(void)
{
}
/** set the position of the matrix manipulator using a 4x4 Matrix.*/
void TravelManipulator::setByMatrix(const osg::Matrixd& matrix)
{

}

/** set the position of the matrix manipulator using a 4x4 Matrix.*/
void TravelManipulator::setByInverseMatrix(const osg::Matrixd& matrix)
{

}

/** get the position of the manipulator as 4x4 Matrix.*/
osg::Matrixd TravelManipulator::getMatrix() const
{
	osg::Matrixd mat;
	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
		m_vRotation._v[1], osg::Vec3(0.0f,1.0f, 0.0f),
		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));





	return mat * osg::Matrixd::translate(m_vPosition);
}

/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
osg::Matrixd TravelManipulator::getInverseMatrix() const
{
	osg::Matrixd mat;
	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f,0.0f, 0.0f),
		m_vRotation._v[1],osg::Vec3(0.0f, 1.0f, 0.0f),
		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));

	return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_vPosition));
}

void TravelManipulator::KeyAction_i()
{
	if (singal == 0)
	{
		m_cPerson->left_leg_tr->setMatrix(osg::Matrix::translate(1.5,0,-8)*
			osg::Matrix::rotate(angle, osg::Vec3(-1,0,0))*
			osg::Matrix::translate(-1.5,0,8)*
			osg::Matrix::translate(0,-move, 0));
	}
	else if(singal == 1)
	{
		m_cPerson->body_tr->setMatrix(osg::Matrix::translate(0,-move,0));
		m_cPerson->head_tr->setMatrix(osg::Matrix::translate(0,-move,0));
		m_cPerson->left_arm_tr->setMatrix(osg::Matrix::translate(0,-move,0));
		m_cPerson->right_arm_tr->setMatrix(osg::Matrix::translate(0,-move,0));
		m_cPerson->left_leg_tr->setMatrix(osg::Matrix::translate(1.5,0,-8)*
			osg::Matrix::rotate(angle, osg::Vec3(1,0,0))*
			osg::Matrix::translate(-1.5,0,8));
		m_cPerson->left_leg_tr->setMatrix(osg::Matrix::translate(0,-move,0));
		m_cPerson->right_leg_tr->setMatrix(osg::Matrix::translate(0,-move,0));
	}

	singal++;
	singal%=2;
	move++;
}

void TravelManipulator::KeyAction_j()
{
	angle += osg::PI_2;
	m_cPerson->root_tr->setMatrix(osg::Matrix::rotate(angle1, osg::Vec3(0,0,1)));
}

void TravelManipulator::KeyAction_l()
{
	angle1 += osg::PI_2;
	m_cPerson->root_tr->setMatrix(osg::Matrix::rotate(angle1, osg::Vec3(0,0,1)));

}

bool TravelManipulator::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& us)
{
	m_fMouseX = ea.getX();
	m_fMouseY = ea.getY();
	int key = ea.getKey();

	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			angle = osg::PI_2/3;
			switch(ea.getKey())
			{
			case 'i':
				KeyAction_i();
				break;
			case 'j':
				KeyAction_j();
				break;
			case 'l':
				KeyAction_l();
				break;
			case 0x20:
				us.requestRedraw();
				us.requestContinuousUpdate(false);
				break;
			case 0xFF50:
				ChangePosition(osg::Vec3(0,0,m_fMoveSpeed));
				break;
			case 0xFF57:
				ChangePosition(osg::Vec3(0,0,-m_fMoveSpeed));
				break;
			case 0x2B:
				m_fMoveSpeed += 1.0f;
				break;
			case 0x2D:
				m_fMoveSpeed -= 0.1f;
				if(m_fMoveSpeed < 1.0f)
				{
					m_fMoveSpeed = 1.0f;
				}
				break;
			case 0xFF52:
			case 0x57:
			case 0x77:
				ChangePosition(osg::Vec3(0,m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				ChangePosition(osg::Vec3(m_fMoveSpeed * cosf(osg::PI_2) + m_vRotation._v[2], 0,0));

				break;
			case 0xff54:
			case 0x53:
			case 0x73:
				ChangePosition(osg::Vec3(0,-m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2) + m_vRotation._v[2], 0,0));

				break;
			case 0x41:
			case 0x61:
				ChangePosition(osg::Vec3(0,m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2) + m_vRotation._v[2], 0,0));
				break;
			case 0x44:
			case 0x64:
				ChangePosition(osg::Vec3(0,-m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				ChangePosition(osg::Vec3(m_fMoveSpeed * cosf(osg::PI_2) + m_vRotation._v[2], 0,0));
				break;
			case 0xff53:
				m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
				
				break;
			case 0xff51:
				m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);


				break;
			case 0x46:
			case 0x66:
				m_fAngle -=0.2;
				break;
			default:

				break;
				
			}


		}
		break;
	case (osgGA::GUIEventAdapter::PUSH):
		{
			if(ea.getButton() == 1)
			{
				m_fpushX = m_fMouseX;
				m_fpushY = m_fMouseY;
				m_bLeftButtonDown = true;
			}



		}


		break;
	case (osgGA::GUIEventAdapter::DRAG):
		if(m_bLeftButtonDown )
		{
			m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle *(m_fMouseX - m_fpushY))/200;
			m_vRotation._v[0] += osg::DegreesToRadians(1.1 * (m_fMouseY - m_fpushY))/200;
			if(m_vRotation._v[0] >= 3.14)
			{
				m_vRotation._v[0] = 3.14;

			}
			if(m_vRotation._v[0] <= 0)
			{
				m_vRotation._v[0] = 0;
			}
		}


		break;
	case (osgGA::GUIEventAdapter::RELEASE):
		if (ea.getButton() == 1)
		{
			m_bLeftButtonDown = false;
		}


		break;

	}



	return false;
}
void TravelManipulator::setPerson(Person* perosn)
{
	m_cPerson = perosn;
}
//void TravelManipulator::setRobot(Robot* perosn)
//{
//	m_cPerson = perosn;
//}
void TravelManipulator::ChangePosition(osg::Vec3 & delta)
{
	if(m_bPeng)
	{
		osg::Vec3 newPOs1 = m_vPosition + delta;
		//osgUtil::IntersectVisitor ivXY;
		//osgUtil::IntersectionVisitor iv;
		osgUtil::LineSegmentIntersector::Intersections intersections;
		osg::ref_ptr<osgUtil::LineSegmentIntersector> ls = new osgUtil::LineSegmentIntersector(newPOs1, m_vPosition);
		osg::ref_ptr<osgUtil::IntersectionVisitor> iv = new osgUtil::IntersectionVisitor(ls);

		//osgUtil::LineSegmentIntersector::Intersection ivXY;
		osg::ref_ptr<osg::LineSegment> lineXY = new osg::LineSegment(newPOs1, m_vPosition);
		osg::ref_ptr<osg::LineSegment> lineZ = new osg::LineSegment(newPOs1 + osg::Vec3(0.0f, 0.0f, 10.0f),
			newPOs1 - osg::Vec3(0.0f, 0.0f, -10.0f));
		///ivXY.addLineSegment( lineZ.get());
		//ivXY.addLineSegment( lineXY.get());
		//ivXY.Line
		//m_pHostViewer.getSceneData()->accept(ivXY);
		m_vPosition += delta;
		//if(!ivXY.hits())
		//{
		//
		//	m_vPosition += delta;
		//}
		//else
		//{
		//	m_vPosition += delta;
		//}
	}
}

float TravelManipulator::getSpeed()
{
	return m_fMoveSpeed;
}
void TravelManipulator::setSpeed(float &sp)
{
	m_fMoveSpeed = sp;
}
void TravelManipulator::setPosition(osg::Vec3 &position )
{
	m_vPosition = position;
}
osg::Vec3 TravelManipulator::GetPosition()
{
	return m_vPosition;
}

void TravelManipulator::setViewer(osgViewer::Viewer & viewer)
{
	//m_pHostViewer = viewer;
}