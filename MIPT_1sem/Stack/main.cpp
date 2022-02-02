
/*!
 * @mainpage
 *  \brief     Stack
 *  \author    Michael Pavlov
 *  \author    Mikhail Pavlov
 *  \version   C++20
 *  \date      10.2020
 *  \pre       First initialize the system.
 *  \bug       No
 *  \warning
 *  \copyright GNU Public License.
 */
#include <cstdio>


#include "Tests.h"

#define DIE printf("ERROR on line %d\n", __LINE__)
#define asserted || DIE

int main() {
    AllTests();
    /*Stack<double> stk = {};
    stk = Stack<double>(10);
    assert(stk.StackError());
    stk.push(100) asserted;
    stk.push(200) asserted;

    stk.pop() == 200 asserted;

    stk.Destruct();
*/
    return 0;
}
