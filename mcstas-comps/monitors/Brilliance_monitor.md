# The `Brilliance_monitor` Component

*McStas: Special "Brilliance" monitor.*

## Identification

- **Site:** 
- **Author:** Peter Willendrup, derived from TOF_lambda_monitor.comp
- **Origin:** DTU Physics
- **Date:** May 23, 2012

## Description

```text
If used in the right setting, will output "instantaneous" and "mean" brilliances in units of Neutrons/cm^2/ster/AA/s. Conditions for proper units:
<ul>
<li>Use a with a source of area 1x1cm
<li>The source must illuminate/focus to an area of 1x1cm a 1m distance
<li>Parametrise the Brilliance_monitor with the frequency of the source
<li>To not change the source TOF distribution, place the Brilliance monitor close to the source!
</ul>

with a source of area 1x1cm illuminating/focusing to an area of 1x1cm a 1m distance, this monitor will output "instantaneous" and "mean" brilliances in units of Neutrons/cm^2/ster/AA/s

Here is an example of the use of the component. Note how the mentioned Unit conditions are implemented in instrument code.

COMPONENT Source = ESS_moderator_long(
l_low = lambdamin, l_high = lambdamax, dist = 1, xw = 0.01, yh = 0.01,
freq = 14, T=50, tau=287e-6, tau1=0, tau2=20e-6,
n=20, n2=5, d=0.00286, chi2=0.9, I0=6.9e11, I2=27.6e10,
branch1=0, branch2=0.5, twopulses=0, size=0.01)
AT (0, 0, 0) RELATIVE Origin

COMPONENT BRIL = Brilliance_monitor(nlam=196,nt=401,filename="bril.sim",
t_0=0,t_1=4000,lambda_0=lambdamin,
lambda_1=lambdamax, Freq=14)
AT (0,0,0.000001) RELATIVE Source
```

## Input parameters

Parameters in **boldface** are required; the others are optional.

| Name | Unit | Description | Default |
|------|------|-------------|---------|
| nlam | 1 | Number of bins in wavelength | 101 |
| nt | 1 | Number of bins in TOF | 1001 |
| nowritefile | 1 | If set, monitor will skip writing to disk | 0 |
| lambda_0 | AA | Minimum wavelength detected | 0 |
| lambda_1 | AA | Maximum wavelength detected | 20 |
| restore_neutron | 1 | If set, the monitor does not influence the neutron state | 0 |
| **Freq** | Hz | Source frequency. Use freq=1 for reactor source |  |
| tofcuts | 1 | Flag to generate TOF-distributions as function of wavelength | 0 |
| toflambda | 1 | Flag to generate TOF-lambda distribution output | 0 |
| xwidth | m | width of monitor | 0.01 |
| yheight | m | height of monitor | 0.01 |
| source_dist | m | Distance from source. Beware when transporting through neutron optics! | 1 |
| filename | string | Defines filenames for the detector images. Stored as:<br>Peak_&lt;filename&gt; and Mean_&lt;filename&gt; | 0 |
| t_0 | us | Minimum time | 0 |
| t_1 | us | Maximum time | 20000 |
| srcarea | cm^2 | Source area | 1 |

## Links

- [Source code](Brilliance_monitor.comp) for `Brilliance_monitor.comp`.

---

*Generated on mcstas 3.99.99.*