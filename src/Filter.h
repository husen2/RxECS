////////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2021.  Shane Hyde (shane@noctonyx.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

//
// Created by shane on 14/06/2021.
//

#ifndef RXECS_FILTER_H
#define RXECS_FILTER_H

#include <vector>
#include <functional>
#include "Entity.h"
#include "TableView.h"

namespace ecs
{
    struct Filter
    {
        struct TableViewIterator
        {
            uint32_t row;
            const Filter * result;

            bool operator!=(const TableViewIterator & rhs) const
            {
                return row != rhs.row;
            }

            void operator++()
            {
                row++;
            }

            const TableView & operator*() const
            {
                return result->tableViews.at(row);
            };
        };

    private:
        World * world;
        std::vector<TableView> tableViews{};

    public:
        explicit Filter(World * world, std::vector<TableView>  tableViews = {});

        void toVector(std::vector<entity_t> & vec) const;
        void each(std::function<void(EntityHandle)> && f) const;
        [[nodiscard]] size_t count() const;

        [[nodiscard]] TableViewIterator begin() const
        {
            return TableViewIterator{0, this};
        }

        [[nodiscard]] TableViewIterator end() const
        {
            return TableViewIterator{static_cast<uint32_t>(tableViews.size()), this};
        }
    };
}
#endif //RXECS_FILTER_H
