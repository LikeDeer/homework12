/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)		// 선택 정렬 : 최소값을 배열의 제일 앞으로 보내는 것을 반복
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;		// i 번째 요소를 교환할 차례 (0 ~ 끝까지)
		min = a[i];			// i 번째 요소를 최소값으로 가정. 최소값 변수에 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)	// i 이후에 보다 작은 요소가 있는지
		{										//   탐색하는 반복문
			if (min > a[j])						// j 번째가 작은 것으로 발견되면 그 인덱스 저장
			{									//   이후 더 작은 것이 있는지 끝까지 탐색
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];			// i 와 j 번째 요소를 교환
		a[i] = min;					//
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];			// 정렬된 부분집합 S : a[0] ~ a[i-1]
		j = i;				//   정렬되지 않은 부분집합 U : a[i] ~ a[끝]
		while (a[j-1] > t && j > 0)		// a[i] 보다 더 큰 요소들을 뒤로 밀어내며, 
		{								//
			a[j] = a[j-1];				//
			j--;						//
		}								//
		a[j] = t;						//   더 작은 요소가 S 에서 발견되면 그 바로 뒤에 삽입
	}									//   (혹은 배열의 처음까지 발견되지 않으면 처음으로 삽입)

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)		// 버블 정렬 : 최대값을 배열의 제일 뒤로 보내는 것을 반복
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)	// 내부 반복문으로 최대값이 뒤에서부터 쌓이고 쌓여, 최종적으로 전체가 정렬될 때 까지 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)	// 최대값을 배열의 제일 뒤로 보내는 반복문
		{
			if (a[j-1] > a[j])			// 인접한 두 원소 중, 앞에 것이 더 크면 교환
			{							//   이를 마지막까지 한 자리씩 옮겨가며 반복
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)		// h 간격 요소들의 부분집합을 삽입 정렬. h = 1이 될 때 까지 반복
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)		// 첫 h 는 배열 크기의 1/2. 단계 반복마다 다시 1/2
	{
		for (i = 0; i < h; i++)		// h 간격 그 사이에 남은 수 (= h) 만큼
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)		// 부분 집합에서 삽입 정렬
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];					// index 에 주의! 큰 것이 뒤로 밀리는 것 : a[k] = a[k-h]
					k -= h;							//
				}
				a[k] = v;					// 부분집합에서 작은 것 뒤에 삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 퀵 정렬 : 피봇(pivot)의 왼쪽은 더 작은 원소들, 오른쪽은 더 큰 원소들로 분할. 그것을 순환적으로 반복
int quickSort(int *a, int n)		// n : 부분 집합의 크기. 처음에는 전체 배열 크기, 점차 분할된 크기로 호출
{
	int v, t;
	int i, j;

	if (n > 1)				// n = 0 이 되면 종료
	{
		v = a[n-1];			// pivot
		i = -1;				// i : 왼쪽 집합의 index
		j = n - 1;			// j : 오른쪽 집합의 index

		while(1)			// pivot의 왼쪽은 더 작은 값, 오른쪽은 더 큰 값의 집합으로 분할하는 반복문
		{
			while(a[++i] < v);		// 왼쪽 집합에서, 왼쪽에서 오른쪽으로 가며 pivot보다 작은 값 찾기
			while(a[--j] > v);		// 오른쪽 집합에서, 오른쪽에서 왼쪽으로 가며 pivot 보다 큰 값 찾기

			if (i >= j) break;
			t = a[i];				// 찾은 그 두 값을 교환
			a[i] = a[j];			//
			a[j] = t;				//
		}
		t = a[i];			// i >= j 되고, 마무리로 한번 더 교환
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);			// 왼쪽 집합의 퀵 정렬 호출
		quickSort(a+i+1, n-i-1);	// 오른쪽 집합의 퀵 정렬 호출
	}


	return 0;
}

int hashCode(int key) {		// key 에 대한 해쉬 코드를 얻는 해쉬 함수(해쉬 테이블의 인덱스)
   return key % MAX_HASH_TABLE_SIZE;	// 우리 프로그램에서 해쉬 코드 생성 원리는 이와 같다.
}

int hashing(int *a, int **ht)	// hash table을 생성. 
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	// 배열의 key 들을 해쉬 테이블에 저장
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);		// key 각각의 해쉬 코드를 얻고
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/

		// 해쉬 테이블에서, 얻은 해쉬 코드 위치가 비어있다면 할당
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)	// 이미 차있다면 다른 빈 곳을 찾아서 할당
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;	// 이 논리를 통해.
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)		// index 를 
{
	int index = hashCode(key);		// 해쉬 함수를 통해 key 에 대한 해쉬 코드를 얻고

	if(ht[index] == key)			// 해쉬 테이블의 위치(해쉬 코드) 에서 키 값을 찾음.
		return index;				//   그 인덱스를 반환

	while(ht[++index] != key)		// 바로 발견하지 못했다면, 해쉬 테이블 생성하는 원리와 동일한 방법으로 탐색
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



