#define MAX_SCHOOLS 3
#define MAX_STUDENTS 10000
#define MAX_CAPACITY 3500

typedef struct
{
	int index;
	int posX;
	int posY;
	int capacity;
	int assigned_students;
} School;

typedef struct
{
	int index;
	int posX;
	int posY;
	int assigned_school;
	double distance_to_school;
} Student;

void get_school_position(int school_index, int* posX, int* posY);
void get_student_position(int student_index, int* posX, int* posY);
void set_student_school(int student_index, int school_index);


double sqrt(double n)
{
	double s = 0;
	double t = 0;

	s = n / 2;

	for (; s != t;)
	{
		t = s;
		s = ((n / t) + t) / 2;
	}

	return s;
}


double calculate_distance(int x1, int y1, int x2, int y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void update_student_distances(Student students[], School schools[])
{
	for (int i = 0; i < MAX_SCHOOLS; ++i)
	{
		for (int j = 0; j < MAX_STUDENTS; ++j)
		{
			if (students[j].assigned_school == -1)
			{
				students[j].distance_to_school = calculate_distance(students[j].posX, students[j].posY, schools[i].posX, schools[i].posY);
			}
		}

		for (int j = 0; j < MAX_STUDENTS; ++j)
		{
			for (int k = j + 1; k < MAX_STUDENTS; ++k)
			{
				if (students[j].distance_to_school < students[k].distance_to_school)
				{
					Student temp = students[j];
					students[j] = students[k];
					students[k] = temp;
				}
			}
		}
	}
}

void assign_students(Student students[], School schools[])
{
	update_student_distances(students, schools);

	int student_index = 0;

	while (student_index < MAX_STUDENTS)
	{
		for (int i = 0; i < MAX_SCHOOLS && student_index < MAX_STUDENTS; ++i)
		{
			if (schools[i].assigned_students < MAX_CAPACITY)
			{
				while (students[student_index].assigned_school != -1 && student_index < MAX_STUDENTS)
				{
					student_index++;
				}
				if (student_index < MAX_STUDENTS)
				{
					students[student_index].assigned_school = i;
					schools[i].assigned_students++;
					set_student_school(student_index, i);
					student_index++;
				}
			}
		}
	}
}

void run_contest(void)
{
	School schools[MAX_SCHOOLS];
	Student students[MAX_STUDENTS];

	for (int i = 0; i < MAX_SCHOOLS; ++i)
	{
		get_school_position(i, &schools[i].posX, &schools[i].posY);
		schools[i].index = i;
		schools[i].capacity = MAX_CAPACITY;
		schools[i].assigned_students = 0;
	}

	for (int i = 0; i < MAX_STUDENTS; ++i)
	{
		get_student_position(i, &students[i].posX, &students[i].posY);
		students[i].index = i;
		students[i].assigned_school = -1;
		students[i].distance_to_school = 0.0;
	}

	assign_students(students, schools);

}