#include"HistoryPage.h"
#include "sqlite/sqlite3.h"


HistoryPage::HistoryPage()
{
	
}

void HistoryPage::SetHistoryPage()
{
	sqlite3* db;
	const char* zErrMsg = 0;
	int rc;
	std::string sql;
	const char* data = "Callback function called";
	rc = sqlite3_open("SaveGames.db", &db);

	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}


	BeginDrawing();
	ClearBackground(BLACK);
	//DrawCircle(530, 350, 350, RED);
	DrawText("Game History ", 400, 100, 40, RAYWHITE);

	sqlite3_stmt* t_statement;

	sql = "SELECT NAME,Money,Result,Time from NewPlayers ORDER BY Time DESC";
	std::string strQuery(sql);
	char* strQuery2 = &strQuery[0];
	size_t t_len = strlen(strQuery2);

	int rc2 = sqlite3_prepare_v2(db, strQuery2, t_len, &t_statement, &zErrMsg);
	int num_cols = sqlite3_column_count(t_statement);
	if (rc2 == SQLITE_OK)
	{
		int i = 0;
		int y_axis = 180;
		int x_axis = 200;
		int rc3 = sqlite3_step(t_statement);

		bool done = false;
		while (!done)
		{
			switch (sqlite3_step(t_statement))
			{
				case SQLITE_ROW:
				{
					for (int i = 0; i < num_cols; i++)
					{
						std::string str = std::string(reinterpret_cast<const char*>(sqlite3_column_text(t_statement, i)));
						DrawText(str.c_str(), x_axis, y_axis, 20, RAYWHITE);
						x_axis += 135;
					}
					x_axis = 200;
					y_axis += 30;
					break;
				}

				case SQLITE_DONE:
				{
					sqlite3_finalize(t_statement);
					done = true;
					break;
				}

			sqlite3_finalize(t_statement);
			}
		}
	}
	else
	{
		const char* db_error_msg = sqlite3_errmsg(db);
	}
	DrawText("Press Backspace to go Menu page", 350, 650, 20, RAYWHITE);
	EnableEventWaiting();
	EndDrawing();
}

HistoryPage::~HistoryPage()
{

}