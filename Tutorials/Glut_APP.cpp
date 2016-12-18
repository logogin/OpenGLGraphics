//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USELIB("D:\Programs\Glut\glut32.lib");
USEUNIT("Gasket3.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
