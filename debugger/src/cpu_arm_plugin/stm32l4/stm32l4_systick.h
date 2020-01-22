/*
 *  Copyright 2020 Sergey Khabarov, sergeykhbr@gmail.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef __DEBUGGER_SRC_STM32L4XX_STM32L4_SYSTICK_H__
#define __DEBUGGER_SRC_STM32L4XX_STM32L4_SYSTICK_H__

#include "iclass.h"
#include "iservice.h"
#include "coreservices/imemop.h"
#include "generic/mapreg.h"
#include "generic/rmembank_gen1.h"

namespace debugger {

class STM32L4_SysTick : public IService {
 public:
    explicit STM32L4_SysTick(const char *name);

    /** IService interface */
    virtual void postinitService() override;

 protected:

    MappedReg32Type STK_CTRL;          // 0x00
    MappedReg32Type STK_LOAD;          // 0x04
    MappedReg32Type STK_VAL;           // 0x08
    MappedReg32Type STK_CALIB;         // 0x0C
};

DECLARE_CLASS(STM32L4_SysTick)

}  // namespace debugger

#endif  // __DEBUGGER_SRC_STM32L4XX_STM32L4_SYSTICK_H__
