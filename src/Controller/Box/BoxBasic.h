//
// Created by chaed on 19. 4. 21.
//

#ifndef UICLASSEXAMPLE_BOXBASIC_H
#define UICLASSEXAMPLE_BOXBASIC_H

#include "../Border.h"

namespace sdleasygui {

struct BoxItem
{
    BoxItem() = default;

    BoxItem(const BoxItem& item)
    {
        if(this == &item)
            return;
        this->color = item.color;
        this->idx = item.idx;
        this->font = item.font;
    }

    virtual ~BoxItem() = default;

    virtual const std::string& getString() const noexcept =  0;

    std::size_t idx;
    TColor color;
    TFont font;
};

class BoxBasic : public Border {
public:

protected:

    BoxBasic(ControllerBuilder &bld);
    virtual ~BoxBasic();

    virtual void onDraw() override;

    virtual void initialize() override
    {
        Border::initialize();
    }

private:

};

}

#endif //UICLASSEXAMPLE_BOXBASIC_H
