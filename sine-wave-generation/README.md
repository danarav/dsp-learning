# Samples and Signals
### What is a Signal?
In the real world, sound is a physical phenomenon — air pressure changing over time. Your eardrum vibrates because air molecules are being pushed and pulled at different rates. That continuous change in air pressure over time is an **analog signal**.
A signal has two axes:

- Time — the horizontal axis, continuous in the real world
- Amplitude — the vertical axis, the strength or magnitude of the signal at any moment

The problem is computers can't work with continuous signals. They can only work with numbers at discrete points in time. So we need to convert the analog signal into something a computer understands — and that process is called **sampling**.

---

### Sampling — Turning Continuous into Discrete
**Sampling** is the process of measuring the amplitude of a signal at regular intervals and storing each measurement as a number.
Each individual measurement is called a sample.
The rate at which we take these measurements is called the sample rate — measured in Hz (**samples per second**).

The most common sample rate you'll encounter is **44,100 Hz** — meaning we take 44,100 snapshots of the audio signal every single second. This is the standard for CDs and most audio software including JUCE.

Why 44,100 specifically? This comes from the **Nyquist Theorem**, which states:
>To accurately represent a signal, your sample rate must be at least twice the highest frequency you want to capture.

Humans can hear up to roughly 20,000 Hz. So we need a sample rate of at least 40,000 Hz. 44,100 gives us comfortable headroom above that. Sample rates below this would cause aliasing — a form of distortion where high frequencies fold back and appear as wrong, lower frequencies.

---

### What is a Sine Wave?
The sine wave is the most fundamental signal in all of DSP. Every sound — a guitar, a voice, a drum — can be broken down into a sum of sine waves at different frequencies and amplitudes. This is the core idea behind the Fourier Transform, which you'll get to later.
A sine wave is defined by three things:
1. **Frequency (Hz)**
   How many complete cycles the wave completes per second. 440 Hz means 440 complete cycles per second — this is the musical note A4, the standard tuning reference.
2. **Amplitude**
   The peak height of the wave. In audio, this corresponds to loudness. An amplitude of 1.0 is the maximum before clipping. You'll typically keep it at 0.5 or below for safety.
3. **Phase**
   Where in its cycle the wave starts. Two sine waves at the same frequency but different phases can cancel each other out completely — this is called phase cancellation and it's critical in audio engineering.

Mathematically a sine wave is:

```y(t) = amplitude × sin(2π × frequency × t)```

Where ```t``` is time in seconds. This formula gives you the amplitude of the wave at any point in time.

---

### From Math to Samples

Since we're working with discrete samples rather than continuous time, we replace ```t``` with ```i / sampleRate``` where ```i``` is the sample index:

```y(i) = amplitude × sin(2π × frequency × (i / sampleRate))```

So for sample index 0:

```
t = 0 / 44100 = 0.0 seconds
y = 0.5 × sin(2π × 440 × 0.0) = 0.0
```

For sample index 1:

```
t = 1 / 44100 = 0.0000226 seconds
y = 0.5 × sin(2π × 440 × 0.0000226) = 0.0312...
```

Each sample is just a number between -1.0 and 1.0. A full second of audio at 44,100 Hz is just a vector of 44,100 of these numbers.

---

### Phase Increment — The Efficient Way

Computing ```2π × frequency × (i / sampleRate)``` every single sample works but is inefficient. In real audio processing you're doing this millions of times per second.
The smarter approach is to calculate how much the phase advances per sample — called the **phase increment** — and just add it each iteration:

```phaseIncrement = 2π × frequency / sampleRate```

Then each sample:

```
phase += phaseIncrement
sample = amplitude × sin(phase)
```

Same result, one multiplication and one addition per sample instead of three operations. This is how oscillators are implemented in real audio software.

*Generated using Claude Sonnet 4.6*