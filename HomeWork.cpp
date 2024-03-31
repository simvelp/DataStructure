#define first_homework
#define sixth_class

#ifdef first_homework

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct student {
	int no;
	char name[6];
	int score;
};
struct new_student { // read db -> struct
	int no;
	char name[6];
	int score;
};
struct log_student {
	int no;
	char name[6];
	int score;
};
int numOfST = 10000;


// �л���� �ֽ�ȭ �Լ�
void update_file(student* student_rec, int *numOfST) {
	FILE* filep = fopen("student_list.txt", "wt");
	if (filep == NULL) {
		printf("file open error\n");
		exit(-1);
	}

	for (int i = 0; i < *numOfST; i++) {
		fprintf(filep, "%d %s %d\n", student_rec[i].no, student_rec[i].name, student_rec[i].score);
	}

	fclose(filep);

	FILE* file_log = fopen("temp_log.txt", "a");
	if (file_log == NULL) {
		printf("file open error\n");
		exit(-1);
	}
	for (int i = 0; i < *numOfST; i++) {
		fprintf(file_log, "%d %s %d\n", student_rec[i].no, student_rec[i].name, student_rec[i].score);
	}

	fclose(file_log);
}

// ���ο� �л� ���Ա��
void insert_student(struct student** student_rec, char* mode, int no, char* name, int score, int * numOfST) {
	if (no <= 0) {
		no = 1;
	}
	else if (*numOfST < no) {
		no = *numOfST + 1;
	}

	*numOfST += 1;
	struct student* tempo = NULL;
	tempo = (student*)realloc(*student_rec, sizeof(struct student) * (*numOfST));
	

	if (tempo == NULL) {
		printf("realloc failed\n");
		return;
	}

	
	*student_rec = tempo;

	for (int i = *numOfST - 2; i >= no - 1; i--) {
		(*student_rec)[i + 1] = (*student_rec)[i];
	}

	(*student_rec)[no - 1].no = no;
	strncpy((*student_rec)[no - 1].name, name, sizeof((*student_rec)[no - 1].name) - 1);
	(*student_rec)[no - 1].name[5] = '\0';
	(*student_rec)[no - 1].score = score;

	for (int i = no; i < *numOfST; i++) {
		(*student_rec)[i].no = i + 1;
	}

	update_file(*student_rec, numOfST);

	printf("insert operating complete.\n");
	printf("\n");

	
}

// �л��� ��Ͽ��� �������
void delete_student(struct student** student_rec, char* mode, int no, char* name, int score,int * numOfST){
	struct student* tempo = NULL;
	struct data_student* tempo2 = NULL;
	for (int i = 0; i < *numOfST; i++) {
		if (strcmp((*student_rec)[i].name, name) == 0) {
			for (int j = i; j < *numOfST; j++) {
				(*student_rec)[j] = (*student_rec)[j + 1];
				(*student_rec)[j].score = (*student_rec)[j + 1].score;
				(*student_rec)[j].no = ((*student_rec)[j + 1].no) - 1;
			}
			break;
		}
	}
	*numOfST -= 1;
	tempo = (student*)realloc(*student_rec, sizeof(struct student) * (*numOfST));
	if (tempo == NULL) {
		printf("realloc failed\n");
		return;
	}
	*student_rec = tempo;
	
	update_file(*student_rec, numOfST);

	printf("delete operating complete.\n");
	printf("\n");
	
}

// sort�Լ�
void sorting(struct student* a, struct student *b) {
	struct student tmp = *a;
	*a = *b;
	*b = tmp;
}

// �̸��� ���������� sort
void sorting_name(int *numOfST, struct student **student_rec) {
	for (int i = 0; i < *numOfST - 1; i++) {
		for (int j = i + 1; j < *numOfST; j++) {
			if (strcmp((*student_rec)[i].name, (*student_rec)[j].name) > 0) // strcmp�Լ����� �̸��� ���������� �����ϴ� ���.
				sorting(&(*student_rec)[i], &(*student_rec)[j]);

		}
	}
	
	update_file(*student_rec, numOfST);
	
	printf("sort name operating complete.\n");
	printf("\n");
}

// ������ ������������ sore
void sorting_score(int* numOfST, struct student** student_rec) {
	for (int i = 0; i < *numOfST - 1; i++) {
		for (int j = i + 1; j < *numOfST; j++) {
			if ((*student_rec)[i].score < (*student_rec)[j].score) sorting(&(*student_rec)[i], &(*student_rec)[j]);
		}
	}
	update_file(*student_rec, numOfST);
	printf("sort score operating complete.\n");
	printf("\n");
	
}

// read DB name ���
void read_file(char* file_name, int* numOfST) {
	int no = 0, score = 0, check = 0;
	char name[6] = { 0 };
	char full_file_name[256];

	sprintf(full_file_name, "%s", file_name);

	FILE* filep = fopen(full_file_name, "r");
	if (filep == NULL) {
		printf("file open error\n");
		exit(-1);
	}
	while (fscanf(filep, "%d %5s %d", &no, name, &score) == 3) {
		check++;
	}
	fclose(filep);

	struct new_student* new_students = (struct new_student*)malloc(sizeof(struct new_student) * check);
	if (new_students == NULL) {
		printf("Memory allocation failed\n");
		exit(-1);
	}

	filep = fopen(full_file_name, "r");
	if (filep == NULL) {
		printf("file open error\n");
		free(new_students);
		exit(-1);
	}

	int flag = 0;
	while (fscanf(filep, "%d %5s %d", &no, name, &score) == 3 && flag < check) {
		new_students[flag].no = no;
		new_students[flag].score = score;
		strncpy(new_students[flag].name, name, sizeof(new_students[flag].name) - 1);
		new_students[flag].name[5] = '\0'; 
		flag++;
	}
	fclose(filep);

	for (int i = 0; i < check; i++) {
		printf("%d %s %d\n", new_students[i].no, new_students[i].name, new_students[i].score);
	}
	printf("\n");

	free(new_students);
}

// write DB name���
void write_file(student* student_rec, int * numOfST, char * file_name) {
	int no = 0, score = 0, check = 0;
	char name[6] = {0};
	char full_file_name[256] = {0};
	
	sprintf(full_file_name, "%s", file_name);
 
	struct log_student* new_log = (struct log_student *)malloc(sizeof(struct log_student) * check);
	if (new_log == NULL) {
		printf("Memory allocation failed 1\n");
		exit(-1);
	}

	FILE* filep = fopen("temp_log.txt", "r");
	for (int i = 0; i < check && fscanf(filep, "%d %5s %d", &no, name, &score) == 3; i++) {
		new_log[i].no = no;
		strncpy(new_log[i].name, name, 5);
		new_log[i].name[5] = '\0';
		new_log[i].score = score;
		check++;
	}
	fclose(filep);

	
	FILE* log_file = fopen(full_file_name, "wt");
	if (!log_file) {
		printf("File open error 2\n");
		return;
	}
	for (int i = 0; i < check; i++) {
		fprintf(log_file, "%d %s %d\n", new_log[i].no, new_log[i].name, new_log[i].score);
	}
	fclose(log_file);

	printf("log written at %s\n", file_name);
	free(new_log);
}

// �̸��� �Է��ϴ� �л��� ������ �����ִ� �Լ�
void show_rec(struct student** student_rec, char * name, int no, int score, int * numOfST) {
	
	int idx = 0;
	for (int i = 0; i < *numOfST; i++) {

		if (strcmp((*student_rec)[i].name, name) == 0) {
			printf("%d %s %d\n", (*student_rec)[i].no, (*student_rec)[i].name, (*student_rec)[i].score);
			idx += 1;
			break;
		}
	}
	if (idx == 0) {
		printf("Can not found, try again.\n");
	}
	printf("\n");
}



int main() {
	int no = 0, score = 0;
	char input_line[256] = {0};
	char mode[7] = {0}, name[6] = {0}, file_name[6] = {0}, DB[3] = {0};

	student* student_rec = NULL;

	student_rec = (student*)malloc(sizeof(student) * numOfST);  // numOfST�� ���� int���� ���ؼ� �޸� �Ҵ�
	if (student_rec == NULL) {
		printf("malloc failed\n");
		return -1;
	}


	// �л��� �������� ���Ͽ� �����ؼ� �߰�
	FILE* filep = fopen("student_list.txt", "wt");
	if (filep == NULL) {
		printf("file open error \n");
		exit(-1);
	}

	for (int i = 0; i < numOfST; i++) {
		student_rec[i].no = i + 1;
		for (int j = 0; j < 5; j++) {
			student_rec[i].name[j] = rand() % 24 + 'a';
		}
		student_rec[i].name[5] = '\0';
		student_rec[i].score = rand() % 101;
		fprintf(filep, "%d %s %d \n", student_rec[i].no, student_rec[i].name, student_rec[i].score);
	}
	fclose(filep);


	while (1) {
		printf(">>");

		fgets(input_line, sizeof(input_line), stdin); // �Է� ��ü�� ����.
		int parsed_count = sscanf(input_line, "%6s %d %5s %d %3s %5s", mode, &no, name, &score, DB, file_name);

		if (parsed_count == 4) {
			insert_student(&student_rec, mode, no, name, score, &numOfST);
		}
		else {
			memset(mode, 0, sizeof(mode));
			memset(name, 0, sizeof(name));
			parsed_count = sscanf(input_line, "%s %s", mode, name);
			parsed_count = sscanf(input_line, "%s %s %s", mode, DB, file_name);
	
			if (parsed_count == 2) {
				
				if (strcmp(mode, "delete") == 0) {
					delete_student(&student_rec, mode, no, name, score, &numOfST);

				}
				else if (strcmp(mode, "list") == 0) {
					show_rec(&student_rec, name, no, score, &numOfST);

				}
				else if (strcmp(mode, "sort") == 0) {
					if (strcmp(name, "score") == 0) {
						sorting_score(&numOfST, &student_rec);
					}
					else if (strcmp(name, "name") == 0) {
						sorting_name(&numOfST, &student_rec);
					}
				}
			}
			else if (parsed_count == 3) {
				if (strcmp(mode, "read") == 0) {
					if (strcmp(DB, "DB") == 0 || strcmp(DB, "db") == 0) {
						read_file(file_name, &numOfST);
					}
				}
				else if (strcmp(mode, "write") == 0) {
					if (strcmp(DB, "DB") == 0 || strcmp(DB, "db") == 0) {
						
						write_file(student_rec, &numOfST, file_name);
					}
				}
			}

		}
	}


	free(student_rec);
	return 0;
}

#endif


