/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/
#pragma once

#include <types.hpp>

namespace speaker {

void speaker(uint32 frequency, uint32 duration);
uint8 vdur(uint32 duration);
uint8 vfrg(uint32 frequency);

} // namespace speaker