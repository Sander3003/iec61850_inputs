#ifndef PTRC_H_
#define PTRC_H_

#include "iec61850_model_extensions.h"
#include "inputs_api.h"


#ifdef __cplusplus
extern "C" {
#endif

void PTRC_init(IedServer server, Input* input);

#ifdef __cplusplus
}
#endif


#endif /* PTRC_H_ */