#include "heapsort.h"
void swap(double *a, double *b);

/* Предполагается, что n>0, и по указателям x и y расположены массив из n элементов.
 * Турнирная сортировка или алгоритм heapsort.
 * */
void heapsort(double *x, double *y, int n, int (*p)(double, double))
{
	int k, parent, position, i, child_1, child_2, child, width, width_dynamic, num_position;
	double buffer_y, buffer_x;

	/* Рассматриваем бинарное дерево с корнем y[0], где для любого y[k] потомками являются y[2*k + 1] и y[2*k + 2].
	 * Первый этап алгорима: превратить дерево в дерево, в котором всякая цепочка от корня до любого конечного элемента упорядочена по убыванию.
	 * */
	for( k = 1; k<n; k++ )
	{
		// Поиск позиции, на которую должен перейти a[k]
		for( position = k; position>0; position = parent )
		{
			parent = (int)( (position - 1)/2 );// Индекс родителя a[position]

			if( p(y[parent],y[k])>-1 )
				break;
		}

		buffer_y = y[k];
		buffer_x = x[k];
		for( i = k; i!=position; i = parent )
		{
			parent = (int)( (i - 1)/2 );
			y[i] = y[parent];
			x[i] = x[parent];
		}
		y[position] = buffer_y;
		x[position] = buffer_x;
	}
	// Первый этап закончен. В y[0] находится максимальный элемент.

	/* Второй этап: для всех k = n - 1, .., 1: поменять местами y[0] и y[k], и в массиве первых k элементов массива a восстанавливаем структуру:
	 * всякая цепочка от корня до любого конечного элемента упорядочена по убыванию. */
	for( k = n - 1; k>0; k-- )
	{
		swap(y, y + k);
		swap(x, x + k);

		child_1 = 1;
		child_2 = 2;
		// Поиск позиции, на которую должен перейти a[0] в массиве a длины k
		width = 1;// Число элементов на уровне дерева, на который будет переставлен a[0]
		for( position = 0; position<(k - 1); child_1 = 2*position + 1, child_2 = 2*position + 2)
		{// Много сравнений?
			if( child_2>k )
			{
				break;
			}

			if( (child_2==k) )
			{
				if( p(y[child_1], y[0])>0 )
				{
					position = child_1;
					width *= 2;
				}

				break;
			}

			if( p(y[child_1], y[0])>0 )
			{
				if( p(y[child_2], y[child_1])>0 )
				{
					position = child_2;
				} else
				{
					position = child_1;
				}

				width *= 2;
				continue;
			}

			if( p(y[child_2], y[0])>0 )
			{
				if( p(y[child_1], y[child_2])>0 )
				{
					position = child_1;
				} else
				{
					position = child_2;
				}

				width *= 2;
				continue;
			}

			break;// (y[position]>=y[child1]) && (y[position]>=y[child2])
		}

		buffer_y = y[0];
		buffer_x = x[0];
		width_dynamic = width;// Ширина уровня поддерева, в котором находится a[position]
		num_position = position - width + 1;// Номер позиции в уровне поддерева ширины width_dynamic;
		for( i = 0; i<position; i = child, width_dynamic = (int)(width_dynamic/2) )
		{
			if( num_position<(int)(width_dynamic/2) )
			{
				child = 2*i + 1;
			} else
			{
				child = 2*i + 2;
				num_position -= (int)(width_dynamic/2);
			}

			y[i] = y[child];
			x[i] = x[child];
		}
		y[position] = buffer_y;
		x[position] = buffer_x;
	}
}

void swap(double *a, double *b)
{
	double buffer;

	buffer = *a;
	*a = *b;
	*b = buffer;
}
