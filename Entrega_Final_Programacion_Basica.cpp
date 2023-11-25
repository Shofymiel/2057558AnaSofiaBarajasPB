#include <iostream>
#include <limits>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <stdlib.h> //para new y delete
using namespace std;
struct Cafe_Express
{
	string DatosGenerales, NombreVendedor, fecha;
	int Nticket = 0; //numero de ticket
	float PrecioArticulos = 0;
	int ListaTotal = 0;
	float PrecioUnitario = 0, Descuentos = 0;
	float propina = 0;
	float IVA = 0.16;
	float Total = 0;
	string platos, statusbaja;
};
int ordenes, Nticket = 0;
string platos, NombreVendedor;
Cafe_Express* Restaurante; //PUNTEROS
void altaOrden();
void modificar();
void eliminar();
void listaOrden();
void salir(); //sera por archivos
int main()
{
	int op;
		printf("\t Cafe Express, Restaurante XYZ S.A. de C.V. \n");
		printf("\tBIENVENIDOS!!\n");
		printf("\tSabado 25 de Noviembre del 2023\n");
		printf("\tSeleccione una opcion:\n \t1.Alta Ordenes\n \t2.Modificar Orden\n \t3.Eliminar Orden\n \t4.Lista Ordenes\n \t5.Limpiar pantalla\n \t6.Salir\n");
		scanf_s("%d", &op);
		cin.ignore(numeric_limits< streamsize >::max(), '\n');//limpiar buffer
		switch (op)
		{
		case 1:
			altaOrden();
			return main();
			break;
		case 2:
			modificar();
			return main();
			break;
		case 3:
			eliminar();
			return main();
			break;
		case 4:
			listaOrden();
			return main();
			break;
		case 5:
			system("cls");
			return main();
			break;
		case 6:
			salir();
			exit(1);//sera en forma de archivos para salir
			break;
		default:
			printf("La opcion que selecciono es incorrecta");
			return main();
			break;
		}
	return 0;
	delete Restaurante;
}
void altaOrden()
{
	float PrecioUnitario = 0, Descuentos = 0, Total = 0,propina=0, porcentajePropina=0;
	int propina = 0;
	printf("Cuantas ordenes quiere dar de alta?");
	scanf_s("%d", &ordenes);
	Restaurante = new Cafe_Express[ordenes];

	for (int i = 0; i < ordenes; i++)
	{
		float sumaPrecios = Restaurante[i].PrecioUnitario * Restaurante[i].ListaTotal;;
		printf(" \tNUMERO DE TICKET %d\n ", i + 1);
		printf("-----------------------------------------------------\n ");
		printf("\tSi el precio final es mayor a 250 pesos, se le aplicara un descuento del 30 porciento al precio \n");
		printf("\tIngrese el nombre del vendedor: ");
		getline(cin, Restaurante[i].NombreVendedor);
		while (getchar() != '\n');
		printf("\tIngrese los platos que desea ordenar\n");
		getline(cin, Restaurante[i].platos);
		while (getchar() != '\n');
		printf("\tIngrese el precio del artículo: \n");
		scanf_s("%f", &Restaurante[i].PrecioUnitario);
		printf("\tIngrese la lista total de articulos : \n");
		scanf_s("%d", &Restaurante[i].ListaTotal);
		if (Restaurante[i].ListaTotal >= 2)
		{
			sumaPrecios += Restaurante[i].PrecioUnitario * Restaurante[i].ListaTotal;
		}
		if (sumaPrecios >= 250)
		{
			Restaurante[i].Descuentos = sumaPrecios * 0.30;
			printf("\t¡Felicidades! Ha alcanzado la cantidad necesaria para un descuento del 30 porciento \n");
		}
		else if(sumaPrecios < 250)
		{
			printf("\tSiga comprando para alcanzar la cantidad necesaria para el descuento \n");
		}
		if (Restaurante[i].Descuentos >= 250) //Calculo de Total solo si se aplica el descuento
		{
			Restaurante[i].Total = Restaurante[i].Descuentos * Restaurante[i].ListaTotal * 0.16;
		}
		else if(Restaurante[i].Descuentos < 250)
		{
			// Si no hay descuento, calcular el total sin descuento
			Restaurante[i].Total = sumaPrecios * Restaurante[i].ListaTotal * 0.16;
		}
		int deseaPropina;
		printf("Desea dejar propina? (1 para sí, 0 para no): \n");
		scanf_s("%d", &deseaPropina);
		if (deseaPropina == 1) {
			printf("Cuánto desea dejar como propina (10, 15, 20): \n");
			scanf_s("%f", &porcentajePropina);
			propina = (porcentajePropina / 100.0 + 1) * Restaurante[i].Total;
			Restaurante[i].Total += propina;
		}
		else if (deseaPropina == 0)
		{
			// Verificar si se aplica descuento antes de calcular el total
			if (Restaurante[i].Descuentos >= 250)
			{
				Restaurante[i].Total = Restaurante[i].Descuentos * Restaurante[i].ListaTotal * 0.16;
			}
			else
			{
				// Si no hay descuento, calcular el total sin descuento
				Restaurante[i].Total = Restaurante[i].PrecioUnitario * Restaurante[i].ListaTotal * 0.16;
			}
		}
		printf("El total de la orden es: %f\n", Restaurante[i].Total);
		printf("-----------------------------------------------------\n ");
	}
}
void modificar()
{
	int opModificar = 0, deseaPropina, porcentajePropina; float propina;

	printf(" ingrese el numero de ticket que desea modificar\n");
	scanf_s("%d", &Nticket);
	Nticket = Nticket - 1;
	for (int i = Nticket; i == Nticket; i++)
	{
		if (Restaurante[i].statusbaja == "Eliminado")
		{
			printf("La orden ha sido eliminada %d \n", i + 1);
			printf("ingrese un registro valido \n");
			return modificar();
		}
		printf("Ingrese un numero del 1 al 4 para indicar la modificacion\n");
		printf("\t 1.Platillo\n \t2.Cantidad\n \t3.Nombre Vendedor\n \t4. Propina\n");
		scanf_s("%d", &opModificar);
		while (getchar() != '\n');
		switch (opModificar) {
		case 1: //cambio de platillo o bebida
			printf("Que tipo de platillo o bebida quiere pedir?\n");
			while (getchar() != '\n');
			getline(cin, Restaurante[i].platos);
			break;
		case 2: //cambio de cantidad, si quiere un cafe o dos
			printf("Ingrese la nueva cantidad del artículo escogido: \n");
			scanf_s("%d", &Restaurante[i].ListaTotal);
			break;
		case 3: //cambio de nombre del vendedor
			printf("Ingrese el nuevo nombre del vendedor");
			getline(cin, Restaurante[i].NombreVendedor);
			while (getchar() != '\n');
		case 4: //cambio de propina, si o no poner el 10, 15 o 20%
			printf("Desea dejar propina? (1 para si, 0 para no)\n");
			scanf_s("%d", &deseaPropina);
			if (deseaPropina == 1) {
				printf("Cuánto desea dejar como propina (10, 15, 20): ");
				scanf_s("%d", &porcentajePropina);
				propina = (porcentajePropina / 100.0 + 1) * Restaurante[i].Total;
				Restaurante[i].Total += propina;
			}
			else if (deseaPropina == 0)
			{
				// Verificar si se aplica descuento antes de calcular el total
				if (Restaurante[i].Descuentos >= 250)
				{
					Restaurante[i].Total = Restaurante[i].Descuentos * Restaurante[i].ListaTotal * 0.16;
				}
				else
				{
					// Si no hay descuento, calcular el total sin descuento
					Restaurante[i].Total = Restaurante[i].PrecioUnitario * Restaurante[i].ListaTotal * 0.16;
				}
			}
			printf("El total de la orden es: %f\n", Restaurante[i].Total);
			break;
		default:
			printf("Numero incorrecto, vuelva a intentarlo. Gracias!");
			return modificar();
			break;
		}
	}
}
void eliminar()
{
	int Eliminar = 0;
	printf("Ingrese el numero de ticket a eliminar");
	scanf_s("%d", &Eliminar);
	Eliminar = -1;
	for (int i = Eliminar; i == Eliminar; i++)
	{
		printf("Se ha eliminado con exito! %d", Eliminar + 1);
		Restaurante[i].statusbaja = "Orden eliminada";
	}
}
void listaOrden()
{
	for (int i = 0; i < ordenes; i++)
	{
		if (Restaurante[i].statusbaja != "Eliminada")
		{
			printf("%d \t \n", i + 1);
			printf("%s \t \n", Restaurante[i].platos.c_str());
			printf("%f \t \n", Restaurante[i].PrecioUnitario);
			printf("%d \t \n", Restaurante[i].ListaTotal);
			printf("%f \t \n", Restaurante[i].Descuentos);
			printf("%f \t \n", Restaurante[i].propina);
			printf("%f \t \n", Restaurante[i].Total);
			printf("%s \n", Restaurante[i].statusbaja.c_str());
		}
	}
}
void salir() //archivos
{
	ofstream archivo;
	string CafeArchivo;
	CafeArchivo = "ordenesCafe.dat";
	archivo.open(CafeArchivo.c_str(), ios::out);
	if (archivo.fail())
	{
		printf("Error no se pudo crear el archivo");
		exit(1);
	}
	archivo << "Ordenes" << "\t";
	archivo << "Platos" << "\t";
	archivo << "Precio" << "\t";
	archivo << "Lista Total de Articulos" << "\t";
	archivo << "Descuento" << "\t";
	archivo << "Propinas" << "\t";
	archivo << "Total" << "\t";
	archivo << "Status de orden" << "\n";
	for (int i = 0; i < ordenes; i++)
	{
		archivo << i + 1 << "\t";
		archivo << Restaurante[i].platos << "\t";
		archivo << Restaurante[i].PrecioUnitario << "\t";
		archivo << Restaurante[i].ListaTotal << "\t";
		archivo << Restaurante[i].Descuentos << "\t";
		archivo << Restaurante[i].propina << "\t";
		archivo << Restaurante[i].Total << "\t";
		archivo << Restaurante[i].statusbaja << "\n";
	}
	archivo.close();
}