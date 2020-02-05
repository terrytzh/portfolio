//
//  Main.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <iostream>


int main(int argc, char** argv)
{
    Game g = Game();
    if(g.Initialize()){
        g.RunLoop();
    }
    g.Shutdown();
	return 0;
}
