/*!
 *  @mainpage
 *  @brief     Differetiator
 *  @author    Michael Pavlov
 *  @author    Mikhail Pavlov
 *  @version   C++20
 *  @date      11.2021
 *  @pre       First initialize the system.
 *  @bug       No
 *  @warning   ...
 *  @copyright GNU Public License.
 */

#include "differetiator.h"


int main() {
    Differentiator diff("equation.txt");

    diff.Dump();

    diff.Dump_to_TeX();

    diff.Dump();

    //Differentiator proizv (diff.differentiate());

    //proizv.Dump();

    //proizv.Dump_to_TeX();

    //proizv.optimize();

    //proizv.Dump_to_TeX();

    return 0;
}
