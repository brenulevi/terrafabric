#pragma once

struct Block
{
    enum class Type
    {
        AIR,
        STONE
    };

    Type type;
};