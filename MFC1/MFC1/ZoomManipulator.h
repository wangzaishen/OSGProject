#pragma once
#ifdef _MSC_VER // This check can be removed if you only build for Windows
#pragma warning (push)
#pragma warning (disable : 4005)
#include <safeint.h>
#include <stdint.h>
#pragma warning (default : 4005)
#pragma warning (pop)
#endif
#include <osgGA/CameraManipulator>
#include <osgViewer/Viewer>

class ZoomManipulator :
	public osgGA::CameraManipulator
{
public:
	ZoomManipulator(void);
	ZoomManipulator(  osg::Node* & node);
	~ZoomManipulator(void);

	virtual void setByMatrix(const osg::Matrixd &);
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getMatrix() const ;
	virtual osg::Matrixd getInverseMatrix()const;

	osg::Node* getNode() const;


	bool handle(const osgGA::GUIEventAdapter & ea, osgGA::GUIActionAdapter & us);

private:
	osg::Vec3	_eye;
	osg::Vec3	_direction;
	osg::Vec3	_up;
	osg::Node*	_root;


};

