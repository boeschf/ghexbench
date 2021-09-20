# Results on Betzy (Norway)

|Node   |Memory |#C/T    |CPU VERSION             | #ACCEL  |ACCEL TYPE|
|:------|------:|-------:|:-----------------------|:--------|:---------|
|betzy  |256 GB |128/256 |AMD EPYC 7742 @ 2.25GHz |NO       |          |

## hwloc info

```
depth 0:            1 Machine (type #0)
 depth 1:           2 Package (type #1)
  depth 2:          8 Group0 (type #12)
   depth 3:         32 L3Cache (type #6)
    depth 4:        128 L2Cache (type #5)
     depth 5:       128 L1dCache (type #4)
      depth 6:      128 L1iCache (type #9)
       depth 7:     128 Core (type #2)
        depth 8:    256 PU (type #3)
Special depth -3:   8 NUMANode (type #13)
Special depth -4:   8 Bridge (type #14)
Special depth -5:   5 PCIDev (type #15)
Special depth -6:   6 OSDev (type #16)
```

## Compiler info
Benchmarks were compiled using the following compilers and MPI implementations

* OpenMPI (4.0.5) + GCC (9.3.0)  
  `CXXFLAGS="-Wall -Wextra -Wpedantic -Wno-unknown-pragmas -march=znver2 -funroll-all-loops"`
* Intel MPI + Intel C++ compiler (19.1.1.217)  
  `CXXFLAGS="-march=core-avx2 -fma -ftz -fomit-frame-pointer"`

Below, those configurations are refered to as `ompi` and `impi`, respectively. If for some results there is no explicit tag,
`ompi` was the configuration used.

## JUBE setup
The JUBE XML script is configured through the following tags

* `ompi`, `impi`: toolchain used
* `halfcores`, `allcores`: number of cores per compute node used
* `single_node`, `27_nodes` : number of nodes used
* `mpicart`, `hwcart`: Cartesian communicator implementation

## Domain decomposition

The `allcores` configuration started 128 ranks per compute node, 1 rank per each physical core.
Effectively, 4 cores per L3 cache domain, 16 cores per NUMA node, and 64 cores per socket were started.
The `halfcores` configuration started 64 ranks per compute node. Every second core was used, 
hence 2 cores per L3 cache domain, 8 ranks per NUMA node, and 32 ranks per socket were started.

The below benchmarks present weak scaling, with each rank computing on a 64^3 computational grid.
Within each compute node the ranks were organized into a 3D grid. With the `hwcart` configuration 
the ranks were remapped to a memory domain specific rank grid. For example, the `halfnode` distribution
`--socket 1 1 2 --numa 1 2 2 --l3 2 2 1 --core 2 1 1` results in a `[4 4 4]` rank grid and `[256 256 256]` 
computational grid per node. For `27_nodes` configurations the nodes were further arranged into a 
3D cartesian grid with dimension `[3 3 3]` (`--node 3 3 3`).
Hence the dimensions of the global computational grid was `[768 768 768]`.

When using `mpicart` the rank neighborhood was determined by the `MPI_Cart_*` communicator
and the rank to compute node assignment was done automatically by MPI. For `ompi` we used
`-map-by ppr:32:socket:pe=2 -bind-to core` for `halfcore` setups and `-map-by ppr:64:socket:pe=1 -bind-to core` for 
`allcores` setups. In case of `impi` an equivalent pinning scheme was used. Running the benchmark
only required specifying the global rank grid dimensions, e.g., `--MPICart 12 12 12`.

## Benchmark results
The computational grid was periodic in all dimensions. Single precision, 32-bit floats were used.

### Setup 1

Results for a 64^3 domain with different halos (1,2,4,5) and different number of fields
(1 2 4 8).

For `halfcores` tests the in-node rank grid was `[4 4 4]`, with `hwcart` decomposition  
`--socket 1 1 2 --numa 1 2 2 --l3 2 2 1 --core 2 1 1`.

For `allcores` tests the in-node rank grid was `[4 8 4]`, with `hwcart` decomposition  
`--socket 1 1 2 --numa 1 2 2 --l3 2 2 1 --core 4 1 1`.

For 27-node runs the node grid dimensions were `[3 3 3]`.

#### Single-node tests

The following tables present a human-readable comparison of the different benchmark results.

[`hwcart halfcores`](single_node/halo_fields_halfcores.md)  
[`hwcart allcores`](single_node/halo_fields_allcores.md)  
[`compact` vs `staged`, `halfcores`](single_node/staged.md)  
[`compact` vs `field-by-field`, `halfcores`](single_node/sequence.md)  

Original JUBE output

[`jube run bench.xml --tag single_node ompi halfcores hwcart`](single_node/jube_0.md)  
[`jube run bench.xml --tag single_node ompi allcores hwcart`](single_node/jube_1.md)  
[`jube run bench.xml --tag single_node impi halfcores hwcart`](single_node/jube_2.md)  
[`jube run bench.xml --tag single_node impi allcores hwcart`](single_node/jube_3.md)  

#### 27-node tests

All sorts of [`comparison plots`](27_nodes/plots.md)  

The following tables present a human-readable comparison of the different benchmark results.

[`hwcart halfcores`](27_nodes/halo_fields_halfcores.md)  
[`hwcart allcores`](27_nodes/halo_fields_allcores.md)  
[`mpicart` vs `hwcart`](27_nodes/mpicart_vs_hwcart.md)  
[`compact` vs `staged`, `halfcores`](27_nodes/staged.md)  
[`compact` vs `field-by-field`, `halfcores`](27_nodes/sequence.md)  
