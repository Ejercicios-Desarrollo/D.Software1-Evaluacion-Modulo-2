#pragma once
#include "pch.h"
#include <string>
using namespace std;
const float margenGanancia = 1.3;
enum GAMA {
	ALTA = 3, MEDIA = 2, BAJA = 1
};

enum TIPO_FACTURA {
	A = 1, B = 2, C = 3
};

enum FORMA_DE_PAGO {
	Contado = 1, Financiado = 2, 
	ParcialmenteFinanciado = 3
};

struct Automovil {
	string marca;
	string modelo;
	GAMA gama;
	int añoDeFabricacion;
	float valorResidual;
	int kmRecorridos;
};

struct Factura {
	TIPO_FACTURA tipoFactura;
	float importe;
	Automovil *automovilVendido;
	string fecha;
	string comprador;
	FORMA_DE_PAGO formaDePago;
};

enum TIPO_CUENTA {
	Caja = 1, Mercaderias = 2, Ventas = 3, 
	DeudoresPorVentas = 4, InteresesGanados = 5
};

struct Asiento {
	char signo;
	TIPO_CUENTA tipoDeCuenta;
	float monto;
};

struct NodoAsiento {
	Asiento *asiento;
	NodoAsiento *siguiente;
};

struct ListaAsientos {
	NodoAsiento *primerElemento;
};

struct Movimiento {
	string fecha;
	string hora;
	ListaAsientos *listaAsientos;
	Factura *factura;
	float mercaderia;
	float caja;
	float ventas;
	float deudoresPorVentas;
	float interesesGanados;
};

struct NodoMovimiento {
	Movimiento *movimiento;
	NodoMovimiento *siguiente;
};

struct ListaMovimientos {
	NodoMovimiento *primerElemento;
};

struct LibroDiario {
	ListaMovimientos *listaMovimientos;
};

struct CicloEconomico {
	int año;
	LibroDiario *libroDiario;
};

struct NodoCicloEconomico {
	CicloEconomico *cicloEconomico;
	NodoCicloEconomico *siguiente;
};

struct ListaCicloEconomico {
	NodoCicloEconomico *primerElemento;
};

struct ListaCiclosEconomicos {
	ListaCicloEconomico *listaCicloEconomico;
};

Automovil* automovilCreate(string marca, string modelo, GAMA gama,
	int añoDeFabricacion, float valorResidual, int kmRecorridos);

Factura* facturaCreate(TIPO_FACTURA tipoFactura, Automovil *unAutomovil,
	string fecha, string comprador, FORMA_DE_PAGO formaDePago);

Asiento* asientoCreate();
ListaAsientos* listaAsientosCreate();
NodoAsiento* nodoAsientoCreate(Asiento* unAsiento);
void listaAsientosAgregarNodo(ListaAsientos *lista, NodoAsiento *nodoAsiento);
bool listaAsientosEstaVacia(ListaAsientos *lista);
NodoAsiento* listaAsientosUltimoElemento(ListaAsientos *lista);
Movimiento* movimientoCreate(string hora, Factura *unaFactura);
ListaMovimientos* listaMovimientosCreate();
NodoMovimiento* nodoMovimientoCreate(Movimiento* unMovimiento);
void listaMovimientosAgregarNodo(ListaMovimientos *lista, NodoMovimiento *nodoMovimiento);
bool listaMovimientosEstaVacia(ListaMovimientos *lista);
NodoMovimiento* listaMovimientosUltimoElemento(ListaMovimientos *lista);
LibroDiario* libroDiarioCreate();
CicloEconomico* cicloEconomicoCreate(int año, LibroDiario *libroDiario);
ListaCicloEconomico* listaCicloEconomicoCreate();
NodoCicloEconomico* nodoCicloEconomicoCreate(CicloEconomico *unCicloEconomico);
void listaCicloEconomicoAgregarNodo(ListaCicloEconomico *lista, NodoCicloEconomico *nodoCicloEconomico);
bool listaCicloEconomicoEstaVacia(ListaCicloEconomico *lista);
NodoCicloEconomico* listaCicloEconomicoUltimoElemento(ListaCicloEconomico *lista);
void listaCiclosEconomicosAgregaCiclo(ListaCiclosEconomicos *listaCiclosEconomicos, CicloEconomico* unCicloEconomico);
ListaCiclosEconomicos* listaCiclosEconomicosCreate();

Factura* venderAuto(TIPO_FACTURA tipoFactura, Automovil *unAutomovil, string fecha,
	string comprador, FORMA_DE_PAGO formaDePago);

void listaMovimientosAgregaMovimiento(LibroDiario *libroDiario, Movimiento* unMovimiento);
void listaAsientosAgregaAsiento(Movimiento* unMovimiento, Asiento* unAsiento);
void movimientoCrearAsientos(Movimiento* unMovimiento);

string automovilMostraGama(Automovil* unAutomovil);
string facturaMostraFormaDePago(Factura* unaFactura);
string facturaMostraTipo(Factura* unaFactura);

void mostrarLeyenda(Movimiento* movimientoPrueba);
void movimientoMostraDetalle(Movimiento* movimientoPrueba);
