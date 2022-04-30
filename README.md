# papi_client
task: example task producing same output as rdpmc in this org but using PAPI PMC API.

This API seems to have some overhead collecting data which shows up in the reported stats. It's much leaner than `pcm` with a cleaner API. The build provides `papi_avail` which clearly reports what stats are supported for the CPUs micro architecture, and another program to find the API'S overhead. `pcm` would kill to be that organized. `pcm` gathers a lot of stats for all cores. PAPI seems to allow to easily get only the stats you want on only one thread/core, which is far closer in spirit to `rdpcm` in this org.
