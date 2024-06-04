#define DEPTH_SIZE_P 130
#define STRING_SIZE 12800

char firstOperand[DEPTH_SIZE_P];
char secondOperand[DEPTH_SIZE_P];
char result[DEPTH_SIZE_P];
bool isCurrentOperandNegative = false;
int globalFirstOperandLength;

//f_operand = firstOperand, s_operand = secondOperand, f_isNegative = firstOperandIsNegative, s_isNegative = secondOperandIsNegative, f_length = firstOperandLength, s_length = secondOperandLength
void calculateHexavigesimal(char* firstOperand, char* secondOperand, bool f_isNegative, bool s_isNegative, int f_length, int s_length)
{
	//26진법 계산 A:0 ~ Z:25	

	//char firstOperand[DEPTH_SIZE] = {'C','W','A'};
	//char secondOperand[DEPTH_SIZE] = {'B','Y','A','H'}; //시간 낭비니 파라미터로 Count 추가

	bool isFirstOperandNegative = f_isNegative;
	bool isSecondOperandNegative = s_isNegative;

	globalFirstOperandLength = f_length;
	int secondOperandLength = s_length;

	int firstOperandCoefficients[DEPTH_SIZE_P];
	int secondOperandCoefficients[DEPTH_SIZE_P];

	for (int i = 0; i < DEPTH_SIZE_P; i++)
	{
		firstOperandCoefficients[i] = '\0';
		secondOperandCoefficients[i] = '\0';
	}
	int resultLength;

	if (globalFirstOperandLength >= secondOperandLength)
	{
		resultLength = globalFirstOperandLength + 1;
	}
	else
	{
		resultLength = secondOperandLength + 1;
	}

	for (int i = 0; i < globalFirstOperandLength; i++)
	{
		firstOperandCoefficients[globalFirstOperandLength - i - 1] = firstOperand[i] - 'A';
	}
	for (int i = 0; i < secondOperandLength; i++)
	{
		secondOperandCoefficients[secondOperandLength - i - 1] = secondOperand[i] - 'A';
	}

	//결과가 음수인지 양수인지 구한다.
	if (!isFirstOperandNegative && !isSecondOperandNegative) //add a+b 결과는 무조건 양수
	{
		int carry = 0;
		int index = 0;

		for (int i = 0; i < resultLength; i++)
		{
			int sum = firstOperandCoefficients[i] + secondOperandCoefficients[i] + carry;
			firstOperandCoefficients[i] = sum % 26;
			carry = sum / 26;
		}

		for (int i = resultLength - 1; i >= 0; i--)
		{
			if (i == resultLength - 1 && firstOperandCoefficients[i] == 0)
			{
				continue;
			}

			result[index++] = 'A' + firstOperandCoefficients[i];
		}

		isCurrentOperandNegative = false;
	}
	else if (!isFirstOperandNegative && isSecondOperandNegative) //sub a-b
	{
		if (globalFirstOperandLength < secondOperandLength) // a < b(-) b가 높은 자리여서 결과는 무조건 음수
		{
			int index = 0;

			for (int i = 0; i < secondOperandLength; i++)
			{
				if (secondOperandCoefficients[i] < firstOperandCoefficients[i])
				{
					secondOperandCoefficients[i] += 26;
					secondOperandCoefficients[i + 1]--;
				}
				secondOperandCoefficients[i] -= firstOperandCoefficients[i];
			}

			for (int i = secondOperandLength - 1; i >= 0; i--)
			{
				if (index == 0 && secondOperandCoefficients[0] == '\0')
				{
					continue;
				}
				else
				{
					result[index++] = static_cast<char>('A' + secondOperandCoefficients[i]);
				}
			}

			isCurrentOperandNegative = true;
		}
		else if (globalFirstOperandLength == secondOperandLength) // a == b(-)
		{
			//같은자리수, 가장 높은 자리수 비교
			for (int i = 0; i <= globalFirstOperandLength; i++)
			{
				if (firstOperandCoefficients[globalFirstOperandLength - i] > secondOperandCoefficients[secondOperandLength - i]) //a > b(-) 결과는 무조건 양수
				{
					int index = 0;

					for (int i = 0; i < globalFirstOperandLength; i++)
					{
						if (firstOperandCoefficients[i] < secondOperandCoefficients[i])
						{
							firstOperandCoefficients[i] += 26;
							firstOperandCoefficients[i + 1]--;
						}
						firstOperandCoefficients[i] -= secondOperandCoefficients[i];
					}

					for (int i = globalFirstOperandLength - 1; i >= 0; i--)
					{
						if (index == 0 && firstOperandCoefficients[0] == '\0')
						{
							continue;
						}
						else
						{
							result[index++] = static_cast<char>('A' + firstOperandCoefficients[i]);
						}
					}

					isCurrentOperandNegative = false;
					break;
				}
				else if (firstOperandCoefficients[globalFirstOperandLength - i] < secondOperandCoefficients[secondOperandLength - i])//a < b(-) 결과는 무조건 음수
				{
					int index = 0;

					for (int i = 0; i < secondOperandLength; i++)
					{
						if (secondOperandCoefficients[i] < firstOperandCoefficients[i])
						{
							secondOperandCoefficients[i] += 26;
							secondOperandCoefficients[i + 1]--;
						}
						secondOperandCoefficients[i] -= firstOperandCoefficients[i];
					}

					for (int i = secondOperandLength - 1; i >= 0; i--)
					{
						if (index == 0 && secondOperandCoefficients[0] == '\0')
						{
							continue;
						}
						else
						{
							result[index++] = static_cast<char>('A' + secondOperandCoefficients[i]);
						}
					}

					isCurrentOperandNegative = true;
					break;
				}
				else
				{
					continue;
				}
			}
		}
		else // a > b(-) a가 높은 자리여서 결과는 무조건 양수
		{
			int index = 0;

			for (int i = 0; i < globalFirstOperandLength; i++)
			{
				if (firstOperandCoefficients[i] < secondOperandCoefficients[i])
				{
					firstOperandCoefficients[i] += 26;
					firstOperandCoefficients[i + 1]--;
				}
				firstOperandCoefficients[i] -= secondOperandCoefficients[i];
			}

			for (int i = globalFirstOperandLength - 1; i >= 0; i--)
			{
				if (index == 0 && firstOperandCoefficients[0] == '\0')
				{
					continue;
				}
				else
				{
					result[index++] = static_cast<char>('A' + firstOperandCoefficients[i]);
				}
			}

			isCurrentOperandNegative = false;
		}
	}
	else if (isFirstOperandNegative && !isSecondOperandNegative) //sub b-a
	{
		if (globalFirstOperandLength > secondOperandLength) // a(-) < b b가 높은 자리여서 결과는 무조건 양수
		{
			int index = 0;

			for (int i = 0; i < globalFirstOperandLength; i++)
			{
				if (firstOperandCoefficients[i] < secondOperandCoefficients[i])
				{
					firstOperandCoefficients[i] += 26;
					firstOperandCoefficients[i + 1]--;
				}
				firstOperandCoefficients[i] -= secondOperandCoefficients[i];
			}

			for (int i = globalFirstOperandLength - 1; i >= 0; i--)
			{
				if (index == 0 && firstOperandCoefficients[0] == '\0')
				{
					continue;
				}
				else
				{
					result[index++] = static_cast<char>('A' + firstOperandCoefficients[i]);
				}
			}

			isCurrentOperandNegative = true;
		}
		else if (globalFirstOperandLength == secondOperandLength) // b == a(-)
		{
			//같은자리수, 가장 높은 자리수 비교
			for (int i = 0; i <= globalFirstOperandLength; i++)
			{
				if (firstOperandCoefficients[globalFirstOperandLength - 1] < secondOperandCoefficients[secondOperandLength - 1]) //a(-) < b 결과는 무조건 양수
				{
					int index = 0;

					for (int i = 0; i < secondOperandLength; i++)
					{
						if (secondOperandCoefficients[i] < firstOperandCoefficients[i])
						{
							secondOperandCoefficients[i] += 26;
							secondOperandCoefficients[i + 1]--;
						}
						secondOperandCoefficients[i] -= firstOperandCoefficients[i];
					}

					for (int i = secondOperandLength - 1; i >= 0; i--)
					{
						if (index == 0 && secondOperandCoefficients[0] == '\0')
						{
							continue;
						}
						else
						{
							result[index++] = static_cast<char>('A' + secondOperandCoefficients[i]);
						}
					}

					isCurrentOperandNegative = false;
					break;
				}
				else if (firstOperandCoefficients[globalFirstOperandLength - 1] > secondOperandCoefficients[secondOperandLength - 1]) //a(-) > b 결과는 무조건 음수
				{
					if (firstOperandCoefficients[globalFirstOperandLength - 1] < secondOperandCoefficients[secondOperandLength - 1]) //a(-) < b 결과는 무조건 양수
					{
						int index = 0;

						for (int i = 0; i < secondOperandLength; i++)
						{
							if (secondOperandCoefficients[i] < firstOperandCoefficients[i])
							{
								secondOperandCoefficients[i] += 26;
								secondOperandCoefficients[i + 1]--;

							}
							secondOperandCoefficients[i] -= firstOperandCoefficients[i];
						}

						for (int i = secondOperandLength - 1; i >= 0; i--)
						{
							if (index == 0 && secondOperandCoefficients[0] == '\0')
							{
								continue;
							}
							else
							{
								result[index++] = static_cast<char>('A' + secondOperandCoefficients[i]);
							}
						}

						isCurrentOperandNegative = true;
						break;
					}
				}
				else
				{
					continue;
				}
			}
		}
		else //a(-) < b b가 높은 자리여서 결과는 무조건 양수
		{
			int index = 0;

			for (int i = 0; i < secondOperandLength; i++)
			{
				if (secondOperandCoefficients[i] < firstOperandCoefficients[i])
				{
					secondOperandCoefficients[i] += 26;
					secondOperandCoefficients[i + 1]--;
				}
				secondOperandCoefficients[i] -= firstOperandCoefficients[i];
			}

			for (int i = secondOperandLength - 1; i >= 0; i--)
			{
				if (index == 0 && secondOperandCoefficients[0] == '\0')
				{
					continue;
				}
				else
				{
					result[index++] = static_cast<char>('A' + secondOperandCoefficients[i]);
				}
			}
			isCurrentOperandNegative = false;
		}

	}
	else //add -(a+b) 결과는 무조건 음수
	{
		int carry = 0;
		int index = 0;

		for (int i = 0; i < resultLength; i++)
		{
			int sum = firstOperandCoefficients[i] + secondOperandCoefficients[i] + carry;
			firstOperandCoefficients[i] = sum % 26;
			carry = sum / 26;
		}

		for (int i = resultLength - 1; i >= 0; i--)
		{
			if (i == resultLength - 1 && firstOperandCoefficients[i] == 0)
			{
				continue;
			}

			result[index++] = static_cast<char>('A' + firstOperandCoefficients[i]);
		}

		isCurrentOperandNegative = true;
	}

	for (int i = globalFirstOperandLength; i > -1; i--)
	{
		firstOperand[i] = 0;
		if (i == 0)
		{
			globalFirstOperandLength = 0;
		}
	}

	for (int i = 0; i < resultLength; i++)
	{
		firstOperand[i] = result[i];
		result[i] = 0;
		globalFirstOperandLength++;
		if (i == resultLength - 1)
		{
			resultLength = 0;
		}
	}
}

void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE])
{
	//question example) CBA+GRDAGSDZFFDAFERFEFDAFAFGADFA-ERADFDAZDFWEQQ+FAFDCVARFERAFDFAFADFDAF

	for (int i = 0; i < STRING_SIZE; i++)
	{
		answer[i] = 0;
	}

	int questionSize = sizeof(question);

	int firstOperandLength = 0;
	int secondOperandLength = 0;

	bool isFirst = true;
	bool isNextOperatorNegative = false;

	int operatorCount = 0;

	for (int i = 0; i < STRING_SIZE; i++)
	{
		if (question[i] == '\0')
		{
			calculateHexavigesimal(firstOperand, secondOperand, isCurrentOperandNegative, isNextOperatorNegative, firstOperandLength, secondOperandLength);
			if (isCurrentOperandNegative)
			{
				answer[0] = '-';
				for (int i = 0; i < globalFirstOperandLength; i++)
				{
					answer[i + 1] = firstOperand[i];
				}
				firstOperandLength = 0;
			}
			else
			{
				for (int i = 0; i < globalFirstOperandLength; i++)
				{
					answer[i] = firstOperand[i];
				}
				firstOperandLength = 0;
			}
			if (firstOperand)

				for (int i = 0; i < sizeof(firstOperand); i++)
				{
					firstOperand[i] = 0;
				}
			isCurrentOperandNegative = false;

			break;
		}
		if (question[i] == '+' || question[i] == '-')
		{
			if (operatorCount < 2)
			{
				operatorCount++;
			}

			if (question[i] == '+')
			{
				if (isFirst)
				{
					isFirst = false;
				}
				else
				{
					if (operatorCount >= 2)
					{
						operatorCount = 1;
						calculateHexavigesimal(firstOperand, secondOperand, isCurrentOperandNegative, isNextOperatorNegative, firstOperandLength, secondOperandLength);
						for (int i = secondOperandLength; i > -1; i--)
						{
							secondOperand[i] = -1;

							if (i == 0)
							{
								secondOperandLength = 0;
							}
						}
						//need empty secondOperand					
					}
				}
				isNextOperatorNegative = false;
			}
			else if (question[i] == '-')
			{
				if (isFirst)
				{
					isFirst = false;
				}
				else
				{
					if (operatorCount >= 2)
					{
						operatorCount = 1;

						calculateHexavigesimal(firstOperand, secondOperand, isCurrentOperandNegative, isNextOperatorNegative, firstOperandLength, secondOperandLength);
						for (int i = secondOperandLength; i > -1; i--)
						{
							secondOperand[i] = -1;

							if (i == 0)
							{
								secondOperandLength = 0;
							}
						}
					}
				}
				isNextOperatorNegative = true;
			}
		}
		else
		{
			if (isFirst)
			{
				firstOperand[firstOperandLength++] = question[i];
				isCurrentOperandNegative = false;
			}
			else
			{
				secondOperand[secondOperandLength++] = question[i];
			}
		}

	}
}