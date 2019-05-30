#include "stdafx.h"
#include "osgFrame.h"

osgFrame::osgFrame(HWND hwnd)
{
	m_hwnd = hwnd;
}
osgFrame::~osgFrame()
{

}

void osgFrame::InitOSG()
{
	InitSceneGraph();
	InitCamera();

}

osg::ref_ptr<osg::Group> mroot;
osgViewer::Viewer* mViewer;
void osgFrame::InitSceneGraph()
{
	osg::ref_ptr<osg::Group> mroot  = new osg::Group();
	//root = new osg::Group();
	//root = mroot;
	//root->addChild(osgDB::readNodeFile("free.osg"));
	mroot->addChild(osgDB::readNodeFile("free.osg"));
}
void osgFrame::InitCamera()
{
	RECT rect;
	mViewer = new osgViewer::Viewer();
	::GetWindowRect(m_hwnd, &rect);
	//::GetWindowRect(m_hWnd, &rect);
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = 
		new osg::GraphicsContext::Traits();
	osg::ref_ptr<osg::Referenced> windata = 
		new osgViewer::GraphicsWindowWin32::WindowData(m_hwnd);

	traits->x = 0;
	traits->y = 0;
	traits->width = rect.right - rect.left;
	traits->height = rect.bottom - rect.top;
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->setInheritedWindowPixelFormat = true;
	traits->inheritedWindowData = windata;

	osg::GraphicsContext *gc = osg::GraphicsContext::createGraphicsContext(traits);
	osg::ref_ptr<osg::Camera> camera = new osg::Camera();
	camera->setGraphicsContext(gc);

	camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f, 
		static_cast<double> (traits->width)/ static_cast<double>(traits->height), 1.0, 1000.0);
	mViewer->setCamera(camera);
	mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
	mViewer->setSceneData(mroot);
	mViewer->realize();
	mViewer->getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
	mViewer->getCamera()->setNearFarRatio(0.000003f);



}
void osgFrame::PreFrameUpdate()
{

}
void osgFrame::PostFrameUpdate()
{

}
void osgFrame::Render(void *ptr)
{
	osgFrame *osg = (osgFrame*)ptr;
	osgViewer::Viewer* viewer = osg->getViewer();
	while(!viewer->done())
	{
		osg->PreFrameUpdate();
		viewer->frame();
		osg->PostFrameUpdate();
	}

	_endthread();
}

osgViewer::Viewer* osgFrame::getViewer()
{
	return mViewer;
}