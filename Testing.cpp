int MainFunction();

void MyFunction(int MyInt);

void OtherFunction(int MyInt);


int MainFunction()
{
	return 0;
}

void MyFunction(void(*OtherFunction)(int MyInt))
{

}

void OtherFunction(int MyInt)
{

}