//
// Created by Edouard on 30/11/2017.
//

#include <IA.h>
#include "Core.h"

int main() {
    IA ia;
    Core coreGame;

    ia.update_score_map(11, 10);
    return (coreGame.run());
}