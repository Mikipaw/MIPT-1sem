/*!
 * @mainpage
 *  @brief     List
 *  @author    Michael Pavlov
 *  @author    Mikhail Pavlov
 *  @version   C++23
 *  @date      11.2020
 *  @pre       First initialize the system.
 *  @bug       No
 *  @warning   May be some problems with big numbers due to conversions from size_t to int
 *  @copyright GNU Public License.
 */


#include "Tests.h"

int Interface();

int main() {
    //if (Tests()) return Tests();

    int err_code = Interface();

    return err_code;
}


int Interface(){
    List lst(6);
    lst.Insert(0, 4);
    lst.Insert(1, 3);
    lst.Insert(0, 8);
    lst.Insert(3, 11);
    lst.Delete_elem(2);
    lst.Insert(3, 33);
    lst.Insert(3, 24);
    lst.Insert(5, 19);
    lst.Insert(3, 12);
    lst.Dump();
    lst.Linear();
    lst.Dump();

    return ALL_OK;
};
