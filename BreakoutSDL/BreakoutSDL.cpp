#include "stdafx.h"

#include "Game.h"

int main()
{
#if (DEBUG || _DEBUG)
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // (DEBUG || _DEBUG)

	std::unique_ptr<Game> pGame = std::make_unique<Game>();
	
	if (pGame->Initialize())
	{
		pGame->Run();
	};

	pGame.reset();

    return 0;
}

