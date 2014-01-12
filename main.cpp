#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "tick.hpp"
#include "strategies/simple_pips_diff_trigger.hpp"

int main(int argc, char* argv[])
{
	FILE* 		file = fopen("data/EURUSD.csv", "r");
	char 			buffer[200];
	Tick			tick;
	unsigned	line = 0;
	vector<Strategy*> strategies;

	// strategy
  printf("    Strategy parameters ");
	for(float t = 0.008; t < 0.030; t += 0.002)
	{
		Strategy *strategy = new SimplePipsDiffTrigger(t);
		strategies.push_back(strategy);
		printf(",%9s", strategy->name().c_str());
	}
  printf("\n");

	while(fgets(buffer, 200, file) != NULL)
	{
		tick.time = strtok(buffer, ",");
		tick.bid = atof(strtok(NULL, ","));
		tick.ask = atof(strtok(NULL, ","));
		tick.bid_volume = atof(strtok(NULL, ","));
		tick.ask_volume = atof(strtok(NULL, ","));
		// if (line > 20000000)
			// break;
		line++;

	  for(auto& strategy : strategies)
			strategy->new_tick(tick);

		if (line % 1000000 == 0)
		{
			printf("%s", tick.time.c_str());
			for(auto& strategy : strategies)
				printf(" ,%+8.1f", strategy->gain());
			printf("\n");
		}
	}

	fclose(file);
}
