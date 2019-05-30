#include "stdafx.h"
#include "South.h"


CSouth::CSouth(void):m_fMoveSpeed(1.5f)
	,m_bLeftButtonDown(false)
	,m_fpushX(0)
	,m_fAngle(2.5)
	,m_bPeng(false)
	,m_fpushY(0)
{
	m_vPosition = osg::Vec3(0.0f, 0.0f, 5.0f);
	m_vRotation = osg::Vec3(osg::PI_2, 0.0f, 0.0f);

}
CSouth::~CSouth()
{

}

void CSouth::setByMatrix(const osg::Matrixd& matrix)
{


}

/** set the position of the matrix manipulator using a 4x4 Matrix.*/
void CSouth::setByInverseMatrix(const osg::Matrixd& matrix)
{
}

/** get the position of the manipulator as 4x4 Matrix.*/
osg::Matrixd CSouth::getMatrix()const
{
	osg::Matrixd mat;
	//mat.makeRotate(m_)

	return mat;
}

/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
osg::Matrixd CSouth::getInverseMatrix()const
{
	osg::Matrixd mat;


	return mat;
}


void CSouth::setPeng(bool peng)
{


}
bool CSouth::getPeng()
{

	return false;
}
void CSouth::setFpeng()
{


}
void CSouth::setNode(osg::Node*)
{


}
bool CSouth::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
{

	return false;
}
void CSouth::ChangePosition( osg::Vec3& delt)
{


}
float CSouth::getSpeed()
{

	return 0.0f;
}
void CSouth::setSpeed()
{

}
void CSouth::SetPosition(osg::Vec3 &position)
{

}
void CSouth::SetPosition(double *)
{


}

osg::Vec3 CSouth::GetPosition()
{

	return osg::Vec3(0.0f, 0.0f, 0.0f);
}
void CSouth::computeHomePosition()
{

}
void CSouth::setAngle( float angle)
{

}
float CSouth::getAngle()
{
	return 0.0f;
}