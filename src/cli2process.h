/**	@file cli2process.h

	@attention Copyright: CPqD
	@attention Centro de Pesquisa e Desenvolvimento em Telecomunicacoes
	@attention Classification: Restricted
	@attention Division: DRT - Diretoria de Redes de Telecomunicacoes

	@attention Project name: ONCS-GMPLS
	@version v0
	@author Fábio Dassan dos Santos
	@date 17/06/09
	@brief Header of function to process messages from CLI (implemented
	in C) to classes (implemented in C++).

	@since VER	| DATE	  	| COMMENTS
	@since v0 	- 17/06/09  - File creation.
*/

#ifndef CLI2PROCESS_H_
#define CLI2PROCESS_H_


#include <stdio.h>
#include "../main/Defines.h"
#include <common/ipc/messages/PayloadHandler.h>

/*
 * Declaration of function that are used on C code.
 * This functions may be declared inside "extern c" structure.
 */
void createMessage(	uint32_t 		session,
					enu_PayloadType type,
					PayloadHandler payload,
					uint8_t* 		buffer,
					uint32_t* 		size);

void sendMessage(uint8_t * buffer, uint32_t size);


#endif /* CLI2PROCESS_H_ */

