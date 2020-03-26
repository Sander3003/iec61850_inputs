/*
 *  server_example_goose.c
 *
 *  This example demonstrates how to use GOOSE publishing, Reporting and the
 *  control model.
 *
 */

#include "inputs_api.h"
#include "iec61850_model_input.h"
#include "iec61850_dynamic_model_input.h"

#include "iec61850_server.h"
#include "hal_thread.h" /* for Thread_sleep() */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "static_model.h"

/* import IEC 61850 device model created from SCL-File */
extern IedModel iedModel;
extern IedModel_inputs iedInputModel;

static int running = 0;
static IedServer iedServer = NULL;

void sigint_handler(int signalId)
{
	running = 0;
}

int main(int argc, char** argv) {

	iedServer = IedServer_create(&iedModel);

	GooseReceiver GSEreceiver = GooseReceiver_create();

    SVReceiver SMVreceiver = SVReceiver_create();

	char* ethernetIfcID = "eth0";

	if (argc > 1) {
		ethernetIfcID = argv[1];

		printf("Using GOOSE interface: %s\n", ethernetIfcID);

		/* set GOOSE interface for all GOOSE publishers (GCBs) */
		IedServer_setGooseInterfaceId(iedServer, ethernetIfcID);
		//goose subscriber
		GooseReceiver_setInterfaceId(GSEreceiver, ethernetIfcID);
		SVReceiver_setInterfaceId(SMVreceiver, ethernetIfcID);
	}

	subscribeToInputs(&iedInputModel, GSEreceiver, SMVreceiver);

    GooseReceiver_start(GSEreceiver);
    SVReceiver_start(SMVreceiver);

    if (GooseReceiver_isRunning(GSEreceiver) && SVReceiver_isRunning(SMVreceiver)) 
	{
		printf("receivers working...\n");
	}
	/* MMS server will be instructed to start listening to client connections. */
	IedServer_start(iedServer, 8102);

	if (!IedServer_isRunning(iedServer)) {
		printf("Starting server failed! Exit.\n");
		IedServer_destroy(iedServer);
		exit(-1);
	}

	/* Start GOOSE publishing */
	IedServer_enableGoosePublishing(iedServer);

	running = 1;

	signal(SIGINT, sigint_handler);

	float anIn1 = 0.f;

	while (running) {

	    IedServer_lockDataModel(iedServer);

        IedServer_updateUTCTimeAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn1_t, Hal_getTimeInMs());
	    IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn1_mag_f, anIn1);

	    IedServer_unlockDataModel(iedServer);

	    anIn1 += 0.1;

		Thread_sleep(1000);
	}

	/* stop MMS server - close TCP server socket and all client sockets */
	IedServer_stop(iedServer);

	/* Cleanup - free all resources */
	IedServer_destroy(iedServer);

	GooseReceiver_stop(GSEreceiver);

    GooseReceiver_destroy(GSEreceiver);

	SVReceiver_stop(SMVreceiver);
     /* Cleanup and free resources */
    SVReceiver_destroy(SMVreceiver);
} /* main() */
