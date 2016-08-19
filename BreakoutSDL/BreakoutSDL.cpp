#include "stdafx.h"

#include "Game.h"

int main()
{
#if (DEBUG || _DEBUG)
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // (DEBUG || _DEBUG)

	Game* pGame = new Game();

	if (pGame->Initialize())
	{
		pGame->Run();
	};

	delete pGame;
	pGame = nullptr;

    return 0;
}

