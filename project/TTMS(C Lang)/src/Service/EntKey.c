//
// Created by bronya on 22-6-20.
//

#include "EntKey.h"
#include "../Persistence/EntityKey_Persist.h"

long EntKey_Srv_CompNewKeys(const char *string, int i) {
    return EntKey_Perst_GetNewKeys(string,i);
}

long EntKey_Srv_CompNewKey(const char *string){
    return EntKey_Perst_GetNewKeys(string,1);
}