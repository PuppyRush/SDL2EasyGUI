//
// Created by chaed on 19. 2. 16.
//

#ifndef TETRIS_FIGURE_CLASS_LIST_H
#define TETRIS_FIGURE_CLASS_LIST_H

#include <vector>

#include "BoxBasic.h"

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



class ListBoxBuilder;

class ListBox : public BoxBasic {
public:

    using item_type = BoxItem;
    using item_ptr = std::shared_ptr<item_type>;

    virtual ~ListBox() = default;
    explicit ListBox(ListBoxBuilder& bld);

    void appendItem(const item_ptr item)
    {
        m_items.push_back(item);
    }

    item_ptr at(const size_t index)
    {
        assert(m_items.size() > index);
        return m_items.at(index);
    }

    virtual void onDraw() override;

    virtual void initialize() override
    {
        BoxBasic::initialize();
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

    virtual Controller::controll_ptr build() final {
        return new ListBox(*this);
    }

};

}

#endif //TETRIS_FIGURE_CLASS_LIST_H
