extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);

int ssp[10];

void target_pick(int targetNum, int hold, int current_stack)
{
	if (targetNum % 2 != 0)
	{
		while (ssp[current_stack] > 0)
		{
			hold = my_pop(current_stack);
			--ssp[current_stack];

			if (hold == targetNum)
			{
				enqueue();
			}
			else
			{
				my_push(0);
				ssp[0]++;
			}
		}
	}
	else
	{
		while (ssp[0] > 0)
		{
			hold = my_pop(0);
			--ssp[0];
			if (hold == targetNum)
			{
				enqueue();
			}
			else
			{
				my_push(current_stack);
				ssp[current_stack]++;
			}
		}
	}
}

void test_main(void)
{
	int hold;

	ssp[0] = 10000;

	while (ssp[0] > 0)
	{
		int target_stack;
		hold = my_pop(0);
		--ssp[0];		

		if (0 == hold)
		{
			enqueue();
		}
		else
		{
			if (hold < 1017)
			{
				target_stack = hold / 113;
			}
			else
			{
				target_stack = 8;
			}
			my_push(target_stack + 1);
			ssp[target_stack + 1]++;
		}
	}

	int checkNum = 112;
	int current_stack = 1;
	int targetNum = 1;

	while (true)
	{
		if (targetNum > 1023)
		{
			break;
		}

		target_pick(targetNum, hold, current_stack);

		++targetNum;
		if (targetNum == checkNum)
		{
			target_pick(targetNum, hold, current_stack);

			if (targetNum < 904)
			{
				checkNum += 113;
				current_stack++;
			}
			else
			{
				checkNum = 1023;
			}
		}
	}
}