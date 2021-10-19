# Project: Sophisticated Player

The pseudo-code could be the following:

1. Choose a target player "i" and her neighbor "j"
2. If there is no neighbor "j" then player "i" moves randomly and go back
   to step 1.
3. Calculate the payoffs of both "i" and "j" and allow "i" to adopt the strategy of "j" by using the usual Fermi-type probability.
4. Check the current (old or newly adopted) strategy of "i". If it is sophisticated, player "i" may move to a neighboring empty space if the current conditions are not satisfactory.
5. Go back to step 1.  and repeat it as many times as the number of players for a full-time step
