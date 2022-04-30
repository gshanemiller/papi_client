# papi_client
task: example task producing same output as rdpmc in this org but using PAPI PMC API.

This API seems to have some overhead collecting data which shows up in the reported stats. It's much leaner than `pcm`. However, it's better than `pcm` in this repository. Also this API is a far nice API, and is much better organized than `pcm`. The build provides `papi_avail` which cleaning reports what stats are supported for the CPUs micro architecture, and another program to find the API'S overhead. `pcm` would kill to be that organized.
