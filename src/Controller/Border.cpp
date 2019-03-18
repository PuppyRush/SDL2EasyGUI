//
// Created by chaed on 19. 1. 22.
//

#include "Border.h"

using namespace sdleasygui;

Border::Border(ControllBuilder& basic)
    :Controll(basic )
{
    basic.kind(ControllKind::Border);
}

void Border::initialize()
{
}


void Border::onDraw()
{
    auto renderer = getWindow()->getSDLRenderer();

    const int x = getPoint().x;
    const int y = getPoint().y;
    const int w = getWidth();
    const int h = getHeight();

    switch(getBorderBoundaryType())
    {
        case BorderBoundaryType::angle: {
            const auto &lineColor = getBorderLineColor();
            const size_t cnt = 5;
            for(int i=0 ; i < getBorderThick() ; i++)
            {
                SDL_Point points[cnt] =
                    {{x+i,y+i},
                     {x+w-i,y+i},
                     {x+w-i,y+h-i},
                     {x+i,y+h-i},
                     {x+i,y+i}};

                SDL_SetRenderDrawColor(renderer, lineColor.r, lineColor.g, lineColor.b, 255);
                SDL_RenderDrawLines(renderer, points, cnt);
            }
        }
        break;
        case BorderBoundaryType::ellipse:
            assert(0);
            break;

        case BorderBoundaryType::round:
            assert(0);
            break;
    }
}
