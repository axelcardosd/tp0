#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;
	int configOk=1;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "<Cliente> Iniciado.");
	log_info(logger, "Hola! Soy un log.");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	 if(config==NULL){
			log_error(logger, "Verifique el archivo de configuracion de entrada. (¿Este existe?)");
			exit(-1);
		}

		if (config_has_property(config, "IP")) {

			ip = config_get_string_value(config, "IP");


		} else {

			log_error(logger, "Error al obtener la IP desde el cliente.config");

			configOk = 0;
		}
		if (config_has_property(config, "PUERTO")) {

			puerto = config_get_string_value(config, "PUERTO");

		} else {

			log_error(logger, "Error al obtener el PUERTO desde el cliente.config");

			configOk = 0;
		}
		if (config_has_property(config, "CLAVE")) {

			valor = config_get_string_value(config, "CLAVE");

		} else {

			log_error(logger, "Error al obtener el CLAVE desde el cliente.config");

			configOk = 0;
		}

		if (!configOk) {
			log_error(logger, "Debido a errores en las configuraciones, se aborta la ejecución... (REVISE ARCH. CONFIGURACIONES)");
			exit(-1);

		}

	// Loggeamos el valor de config
	log_debug(logger, "La IP de SERVIDOR es: %s, su puerto: %s, el valor: %s", ip, puerto,valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	if(conexion==-1){
		log_error(logger, "Problema al levantar conexión con SERVIDOR en IP:%s PUERTO:%s (¿SERVIDOR se encuentra levantado?)",ip,puerto);
		exit(-1);
	}
	log_info(logger,"Conexión establecida con SERVIDOR.");

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("logClient", "CLIENTE LOG", true, LOG_LEVEL_DEBUG);;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	while(1){
	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	if (strcmp(leido, "\0")==0){
			log_info(logger, "Finalizado ingreso de usuario por consola.");
			break;
		}else{
			log_info(logger, leido);
		}
	}

	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_info(logger, "Finalizado el envio de datos. Cliente Cerrado.");
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
