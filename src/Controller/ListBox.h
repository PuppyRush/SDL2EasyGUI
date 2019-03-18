//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_LIST_H
#define TETRIS_FIGURE_CLASS_LIST_H

#include <vector>

#include "Border.h"

namespace sdleasygui {

enum class ListBoxTypes : t_type {
    multiclicked,
    editable,
    clickable,
};

enum class ListBoxScrollType : t_type {
    vertical,
    horizen,
    both
};

struct ListItem
{
    ListItem() = default;

    ListItem(const ListItem& item)
    {
        if(this == &item)
            return;
        this->color = item.color;
        this->idx = item.idx;
        this->font = item.font;
    }

    virtual ~ListItem() = default;

    virtual const std::string& getString() const noexcept =  0;

    std::size_t idx;
    TColor color;
    TFont font;
};

class ListBoxBuilder;

class ListBox : public Border {
public:

    using item_type = ListItem;
    using item_ptr = std::shared_ptr<item_type>;

    virtual ~ListBox() = default;
    explicit ListBox(ListBoxBuilder& bld);

    void appendItem(const item_ptr item)
    {
        m_items.push_back(item);
    }

    virtual void onDraw() override;

    virtual void initialize() override
    {
        Border::initialize();
    }

private:
    std::vector<item_ptr> m_items;

};

class ListBoxBuilder : public BorderBuilder {
public:

    virtual ~ListBoxBuilder() = default;
    ListBoxBuilder(const GraphicInterface::window_type window, const TPoint &point, const std::string &str)
        : BorderBuilder(window, point, str) {
    }

    ListBoxBuilder(const GraphicInterface::window_type window, TPoint &&point, std::string &&str)
        : BorderBuilder(window, point, str) {
    }

    virtual Controll::controll_ptr build() final {
        return new ListBox(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_LIST_H
