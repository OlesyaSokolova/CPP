#pragma once
namespace consts
{
enum Trit { False, Unknown, True };

typedef unsigned int uint;

const uint TRITS_IN_UINT = (sizeof(uint) * 8) / 2; 
}