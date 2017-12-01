//
// Created by Edouard on 30/11/2017.
//

#include <IA.h>
#include "Core.h"

int main()
{
    Core coreGame;
    IA ia;

    ia.find_nb_qtuples(10, 10);
    return (coreGame.run());
}