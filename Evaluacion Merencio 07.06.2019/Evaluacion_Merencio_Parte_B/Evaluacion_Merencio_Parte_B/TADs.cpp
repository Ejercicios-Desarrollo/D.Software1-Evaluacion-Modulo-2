#include "pch.h"
#include "Structs.h"

/*
Lista de Ciclo Economico OK
Ciclo economico (Año, Libro Diario) OK
Un Libro Diario tiene una Lista de Movimientos OK
Movimiento (Fecha, Hora, Lista Asiento) (pago financiado - contado) OK
Lista Asiento (signo, Cuenta, Monto) OK

Movimiento: OK
-Cuenta Caja
-Mercaderias
-Ventas
-Deudores por Ventas
-Intereses Ganados

Vender Auto OK
-> Crear Factura OK
-> Segun fecha cargo en cicloEconomico 
->LibroDiario OK
-> Crear movimiento(fecha, factura) OK
-> Segun pago Agrego Asientos a Lista OK
-> Actualizo cajas movimiento OK
*/

//Funciones

void listaCiclosEconomicosAgregaCiclo(ListaCiclosEconomicos *listaCiclosEconomicos, CicloEconomico* unCicloEconomico) {
	NodoCicloEconomico* nodoCicloEconomico = nodoCicloEconomicoCreate(unCicloEconomico);
	listaCicloEconomicoAgregarNodo(listaCiclosEconomicos->listaCicloEconomico, nodoCicloEconomico);
}

Factura* venderAuto(TIPO_FACTURA tipoFactura, Automovil *unAutomovil, string fecha,
	string comprador, FORMA_DE_PAGO formaDePago) {
	return facturaCreate(tipoFactura, unAutomovil, fecha, comprador, formaDePago);
}

void listaMovimientosAgregaMovimiento(LibroDiario *libroDiario, Movimiento* unMovimiento) {
	NodoMovimiento* nodoMovimiento = nodoMovimientoCreate(unMovimiento);
	listaMovimientosAgregarNodo(libroDiario->listaMovimientos, nodoMovimiento);
}

void listaAsientosAgregaAsiento(Movimiento* unMovimiento, Asiento* unAsiento) {
	NodoAsiento* nodoAsiento = nodoAsientoCreate(unAsiento);
	listaAsientosAgregarNodo(unMovimiento->listaAsientos, nodoAsiento);
}

void movimientoCrearAsientos(Movimiento* unMovimiento) {
	if(unMovimiento->factura->formaDePago == Contado){
		Asiento* asientoMercaderia = asientoCreate();
		asientoMercaderia->monto = unMovimiento->factura->automovilVendido->valorResidual;
		asientoMercaderia->signo = '-';
		asientoMercaderia->tipoDeCuenta = Mercaderias;
		listaAsientosAgregaAsiento(unMovimiento, asientoMercaderia);
		unMovimiento->mercaderia -= asientoMercaderia->monto;

		Asiento* asientoCaja = asientoCreate();
		asientoCaja->monto = unMovimiento->factura->importe;
		asientoCaja->signo = '+';
		asientoCaja->tipoDeCuenta = Caja;
		listaAsientosAgregaAsiento(unMovimiento, asientoCaja);
		unMovimiento->caja += asientoCaja->monto;

		Asiento* asientoVentas = asientoCreate();
		asientoVentas->monto = unMovimiento->factura->importe 
			- unMovimiento->factura->automovilVendido->valorResidual;
		asientoVentas->signo = '+';
		asientoVentas->tipoDeCuenta = Ventas;
		listaAsientosAgregaAsiento(unMovimiento, asientoCaja);
		unMovimiento->ventas += asientoVentas->monto;

	}

	if (unMovimiento->factura->formaDePago == Financiado) {
		Asiento* asientoMercaderia = asientoCreate();
		asientoMercaderia->monto = unMovimiento->factura->automovilVendido->valorResidual;
		asientoMercaderia->signo = '-';
		asientoMercaderia->tipoDeCuenta = Mercaderias;
		listaAsientosAgregaAsiento(unMovimiento, asientoMercaderia);
		unMovimiento->mercaderia -= asientoMercaderia->monto;

		Asiento* asientoDeudoresPorVentas = asientoCreate();
		asientoDeudoresPorVentas->monto = unMovimiento->factura->importe * 1,15;
		asientoDeudoresPorVentas->signo = '+';
		asientoDeudoresPorVentas->tipoDeCuenta = DeudoresPorVentas;
		listaAsientosAgregaAsiento(unMovimiento, asientoDeudoresPorVentas);
		unMovimiento->deudoresPorVentas += asientoDeudoresPorVentas->monto;

		Asiento* asientoInteresesGanados = asientoCreate();
		asientoInteresesGanados->monto = unMovimiento->factura->importe * 0,15;
		asientoInteresesGanados->signo = '+';
		asientoInteresesGanados->tipoDeCuenta = InteresesGanados;
		listaAsientosAgregaAsiento(unMovimiento, asientoInteresesGanados);
		unMovimiento->interesesGanados += asientoInteresesGanados->monto;

		Asiento* asientoVentas = asientoCreate();
		asientoVentas->monto = unMovimiento->factura->importe
			- unMovimiento->factura->automovilVendido->valorResidual;
		asientoVentas->signo = '+';
		asientoVentas->tipoDeCuenta = Ventas;
		listaAsientosAgregaAsiento(unMovimiento, asientoVentas);
		unMovimiento->ventas += asientoVentas->monto;
	}
}


//Fin Funciones

//TAds
Automovil* automovilCreate(string marca, string modelo, GAMA gama,
	int añoDeFabricacion, float valorResidual, int kmRecorridos) {
	Automovil* unAutomovil = new Automovil;
	unAutomovil->marca = marca;
	unAutomovil->modelo = modelo;
	unAutomovil->gama = gama;
	unAutomovil->añoDeFabricacion = añoDeFabricacion;
	unAutomovil->valorResidual = valorResidual;
	unAutomovil->kmRecorridos = kmRecorridos;
	return unAutomovil;
}

Factura* facturaCreate(TIPO_FACTURA tipoFactura, Automovil *unAutomovil,
	string fecha, string comprador, FORMA_DE_PAGO formaDePago) {
	Factura* unaFactura = new Factura;
	unaFactura->tipoFactura = tipoFactura;
	unaFactura->importe = unAutomovil->valorResidual * margenGanancia;
	unaFactura->automovilVendido = unAutomovil;
	unaFactura->fecha = fecha;
	unaFactura->comprador = comprador;
	unaFactura->formaDePago = formaDePago;
	return unaFactura;
}

Asiento* asientoCreate() {
	Asiento* unAsiento = new Asiento;
	unAsiento->monto = 0;
	return unAsiento;
}

ListaAsientos* listaAsientosCreate() {
	ListaAsientos *lista = new ListaAsientos;
	lista->primerElemento = NULL;
	return lista;
}

NodoAsiento* nodoAsientoCreate(Asiento* unAsiento) {
	NodoAsiento *unNodo = new NodoAsiento;
	unNodo->asiento = unAsiento;
	unNodo->siguiente = NULL;
	return unNodo;
}

void listaAsientosAgregarNodo(ListaAsientos *lista, NodoAsiento *nodoAsiento) {
	if (listaAsientosEstaVacia(lista)) {
		lista->primerElemento = nodoAsiento;
	}
	else {
		NodoAsiento *ultimoNodo = listaAsientosUltimoElemento(lista);
		ultimoNodo->siguiente = nodoAsiento;
	}
}

bool listaAsientosEstaVacia(ListaAsientos *lista) {
	return lista->primerElemento == NULL;
}

NodoAsiento* listaAsientosUltimoElemento(ListaAsientos *lista) {
	NodoAsiento *nodoAuxiliar = lista->primerElemento;
	while (nodoAuxiliar->siguiente != NULL) {
		nodoAuxiliar = nodoAuxiliar->siguiente;
	}
	return nodoAuxiliar;
}

Movimiento* movimientoCreate(string hora, Factura *unaFactura) {
	Movimiento* unMovimiento = new Movimiento;
	unMovimiento->fecha = unaFactura->fecha;
	unMovimiento->hora = hora;
	unMovimiento->listaAsientos = listaAsientosCreate();
	unMovimiento->factura = unaFactura;
	unMovimiento->mercaderia = 0;
	unMovimiento->caja = 0;
	unMovimiento->ventas = 0;
	unMovimiento->deudoresPorVentas = 0;
	unMovimiento->interesesGanados = 0;
	return unMovimiento;
}

ListaMovimientos* listaMovimientosCreate() {
	ListaMovimientos *lista = new ListaMovimientos;
	lista->primerElemento = NULL;
	return lista;
}

NodoMovimiento* nodoMovimientoCreate(Movimiento* unMovimiento) {
	NodoMovimiento *unNodo = new NodoMovimiento;
	unNodo->movimiento = unMovimiento;
	unNodo->siguiente = NULL;
	return unNodo;
}

void listaMovimientosAgregarNodo(ListaMovimientos *lista, NodoMovimiento *nodoMovimiento) {
	if (listaMovimientosEstaVacia(lista)) {
		lista->primerElemento = nodoMovimiento;
	}
	else {
		NodoMovimiento *ultimoNodo = listaMovimientosUltimoElemento(lista);
		ultimoNodo->siguiente = nodoMovimiento;
	}
}

bool listaMovimientosEstaVacia(ListaMovimientos *lista) {
	return lista->primerElemento == NULL;
}

NodoMovimiento* listaMovimientosUltimoElemento(ListaMovimientos *lista) {
	NodoMovimiento *nodoAuxiliar = lista->primerElemento;
	while (nodoAuxiliar->siguiente != NULL) {
		nodoAuxiliar = nodoAuxiliar->siguiente;
	}
	return nodoAuxiliar;
}


LibroDiario* libroDiarioCreate() {
	LibroDiario* unLibroDiario = new LibroDiario;
	unLibroDiario->listaMovimientos = listaMovimientosCreate();
	return unLibroDiario;
}

ListaCiclosEconomicos* listaCiclosEconomicosCreate() {
	ListaCiclosEconomicos *listaCiclosEconomicos = new ListaCiclosEconomicos;
	listaCiclosEconomicos->listaCicloEconomico = listaCicloEconomicoCreate();
	return listaCiclosEconomicos;
}

CicloEconomico* cicloEconomicoCreate(int año, LibroDiario *libroDiario) {
	CicloEconomico* unCicloEconomico = new CicloEconomico;
	unCicloEconomico->año = año;
	unCicloEconomico->libroDiario = libroDiario;
	return unCicloEconomico;
}

ListaCicloEconomico* listaCicloEconomicoCreate() {
	ListaCicloEconomico *lista = new ListaCicloEconomico;
	lista->primerElemento = NULL;
	return lista;
}

NodoCicloEconomico* nodoCicloEconomicoCreate(CicloEconomico *unCicloEconomico) {
	NodoCicloEconomico *unNodo = new NodoCicloEconomico;
	unNodo->cicloEconomico = unCicloEconomico;
	unNodo->siguiente = NULL;
	return unNodo;
}

void listaCicloEconomicoAgregarNodo(ListaCicloEconomico *lista, NodoCicloEconomico *nodoCicloEconomico) {
	if (listaCicloEconomicoEstaVacia(lista)) {
		lista->primerElemento = nodoCicloEconomico;
	}
	else {
		NodoCicloEconomico *ultimoNodo = listaCicloEconomicoUltimoElemento(lista);
		ultimoNodo->siguiente = nodoCicloEconomico;
	}
}

bool listaCicloEconomicoEstaVacia(ListaCicloEconomico *lista) {
	return lista->primerElemento == NULL;
}

NodoCicloEconomico* listaCicloEconomicoUltimoElemento(ListaCicloEconomico *lista) {
	NodoCicloEconomico *nodoAuxiliar = lista->primerElemento;
	while (nodoAuxiliar->siguiente != NULL) {
		nodoAuxiliar = nodoAuxiliar->siguiente;
	}
	return nodoAuxiliar;
}
//Fin TAds
