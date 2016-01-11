/**	@file main_cli.c

	@attention Copyright: CPqD
	@attention Centro de Pesquisa e Desenvolvimento em Telecomunicacoes
	@attention Classification: Restricted
	@attention Division: DRT - Diretoria de Redes de Telecomunicacoes

	@attention Project name: ONCS-GMPLS
	@version v0
	@author Fábio Dassan dos Santos / Giovanni Curiel dos Santos / Fabian N.C. van 't Hooft
	@date 28/05/15
	@brief File that starts the CLI based on generated implementations.

	@since VER	| DATE	  	| COMMENTS
    @since v0   - 16/06/09  - File incorporation on project.
    @since v1   - 16/06/09  - File incorporation on project.
*/

#include "zebra.h"
#include "command.h"
#include "vty.h"
#include "thread.h"
#include <string.h>
#include "log.h"

// #include "Ccm_cli_commands.h"

struct thread_master *master;

/**
 * Main function that starts the CLI based on Zebra (Dragon).
 * @param[in]	const char		*	hostname	Interface address of CLI.
 * @param[in]	unsigned short		port		Interface port of CLI.
 */
void start_cli(const char *hostname, unsigned short port)
{


    /* First of all we need logging init. */
    zlog_default = openzlog ("Cli", ZLOG_CPQD,
               LOG_CONS|LOG_NDELAY|LOG_PID, LOG_DAEMON);

	struct thread thread;					// Declare a thread
	master = thread_master_create();		// Starts the master thread

    //char *config_file = NULL;
    /* Get configuration file. */
    //vty_read_config (config_file, "./cliTest.conf");
    cmd_init (1);
    vty_init (master);
/*
    install_element (VIEW_NODE, &ccm_init_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_loopback_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_loopback_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_system_degree_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_system_degree_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_card_wss_status_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_cross_connection_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_single_channel_cross_connection_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_channel_spacing_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_channel_spacing_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_enable_card_wss_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_disable_card_wss_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_remove_card_wss_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_create_cross_connection_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_remove_cross_connection_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_lightpath_wss_order_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_lightpath_wss_order_cmd);
    install_element (VIEW_NODE, &ccm_msg_set_wss_lightpath_number_of_nodes_cmd);
    install_element (VIEW_NODE, &ccm_msg_get_wss_lightpath_number_of_nodes_cmd);
*/
	// Open socket to listen connections
	vty_serv_sock(hostname, port, "/tmp/marben_log");

	// Init socket for communication with MPA
	//init_mpa_socket();

	// While master thread alive, keep listening events
	while (thread_fetch(master, &thread))
	{
		thread_call(&thread);
	}
};

int main(void){
    start_cli("CCM", 5000);
    return 0;
}
