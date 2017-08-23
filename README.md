# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

## Considerations

The 3 parameters have been partially tuned by heand abd partially by using a custom implementation of Twiddle. I started with a twiddle-only approach, with p{0,0,0} and dp{1,1,1} however it was unsucessfull due to the many limitations of the simulator, the track should have allowed the car to just wander off track without gtting stucked, in this way it would have mate possible to "twiddle" from skretch. 
So I decided to start from the parameters given by Sebastian in the class as a starting point for twiddle, I implemented a simple load/save parameter in order to preserve the advancment between runs as well as being able to start and stop the simulation at will.
The major improvment that twiddle did have been to increase the parameter of differencial to limit the overcorrection. As a test I also tried to introduce delta T on the differencial terms, but at the algorithm was running too fast it was resulting into a constant division by 0 (moderated to 0.000001), so for the sake of this project I just assumed that the cte way sampled always at the same rate.

The other great limit I encountered was that in order to make various round of twiddle "comparable" it should have tested on the exact same track, however this would have implied to wait the full round before every adjustment, which is just impractical, so the best option would have been to be able to reset the car position to the origin via API, however the modifications of the simulator in order to do so, wer way beyond the some of this project.

The final parameters can be found in the params.txt (first 3 values)
