/**
 * @file check_serialnumber.cpp
 * @author Taiyou Komazawa (taiyou24690@gmail.com)
 * @brief 現在接続されている(すべての)MCP2210のシリアルナンバーを表示します。
 * @version 0.1
 * @date 2022-01-14
 * 
 * @details 結果はモニターに次の例のように表示される
 * 
 *      MCP2210 SerialNumber List------
 *      File path       : Serial number
 *      /dev/hidraw1    : 0001312251
 *      end----------------------------
 * 
 */

#include "IMDController/IMDController.hpp"

int main()
{
    /* この関数により接続されているMCP2210が列挙される。 */
    IMDController::display_serial_number();
    return 0;
}