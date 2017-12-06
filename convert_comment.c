#include "convert_comment.h"


int status = NULLSTATUS;

void do_null_status(FILE *ifp, FILE *ofp)
{
	int ch = fgetc(ifp);

	switch (ch)
	{
	case '/':
	{
				int s = fgetc(ifp);
				switch (s)
				{
				case '*':
					fputc('/', ofp);
					fputc('/', ofp);
					status = CSTATUS;
					break;

				case '/':
					fputc('/', ofp);
					fputc('/', ofp);
					status = CPPSTATUS;
					break;

				case EOF:
					status = EOFSTATUS;
					break;

				default:
					fputc(ch, ofp);
					ungetc(s, ifp);
					status = NULLSTATUS;
					break;
				}
			break;
	}
	
	case EOF:
		status = EOFSTATUS;
		break;

	default:
		fputc(ch, ofp);
		status = NULLSTATUS;
		break;
	}
}

void do_cpp_status(FILE *ifp, FILE *ofp)
{
	int ch = fgetc(ifp);
	switch (ch)
	{
	case '\n':
		fputc(ch, ofp);
		status = NULLSTATUS;
		break;
	case EOF:
		status = EOFSTATUS;
		break;
	default:
		fputc(ch, ofp);
		status = CPPSTATUS;
		break;
	}
}

void do_c_status(FILE *ifp, FILE *ofp)
{
	int ch = fgetc(ifp);
	switch (ch)
	{
	case '*':
	{
				int s = fgetc(ifp);
				switch (s)
				{
				case '/':
					fputc('\n', ofp);
					status = NULLSTATUS;
					break;

				default:
					fputc(ch, ofp);
					ungetc(s, ifp);
					status = CSTATUS;
					break;
				}
			break;
	}

	case '\n':
		fputc(ch, ofp);
		fputc('/', ofp);
		fputc('/', ofp);
		status = CSTATUS;
		break;

	case EOF:
		status = EOFSTATUS;
		break;

	default:
		fputc(ch, ofp);
		status = CSTATUS;
		break;
	}

}

void do_eof_status(FILE *ifp, FILE *ofp)
{
	return;
}


static void convert_work(FILE *ifp, FILE *ofp)
{
	while (status != EOFSTATUS)
	{
		switch (status)
		{
		case NULLSTATUS:
			do_null_status(ifp, ofp);
			break;

		case CPPSTATUS:
			do_cpp_status(ifp, ofp);
			break;
			
		case CSTATUS:
			do_c_status(ifp, ofp);
			break;
			
		case EOFSTATUS:
			do_eof_status(ifp, ofp);
			break;

		default:
			break;
		}
	}
}

void convert_comment()
{
	FILE *ifp = fopen(INPUTFILE, "r");
	FILE *ofp = fopen(OUTPUTFILE, "w");

	if (ifp == NULL || ofp == NULL)
	{
		perror("fopen");
		return;
	}
	
	convert_work(ifp, ofp);

	fclose(ifp);
	fclose(ofp);
}