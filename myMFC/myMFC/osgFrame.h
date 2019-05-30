#pragma once
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Group>
#include <string>

class osgFrame
{
public:
	osgFrame(HWND hwnd);
	~osgFrame();

	void InitOSG();
	void InitSceneGraph();
	void InitCamera();
	void PreFrameUpdate();
	void PostFrameUpdate();
	static void Render(void *ptr);
	osgViewer::Viewer* getViewer();


//private:
public:
	HWND m_hwnd;
	//osgViewer::Viewer* mViewer;
	//osg::ref_ptr<osg::Group> mRoot;
	//osg::ref_ptr<osg::Group> root;
	//osg::Group* mRoot;
};