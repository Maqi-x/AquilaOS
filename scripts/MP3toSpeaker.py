#!/usr/bin/env python3
from pydub import AudioSegment
import numpy as np
import scipy.fftpack
import sys
from typing import List, Tuple

def mp3ToSpeaker(mp3File: str, stepMs: int = 20, tolerance: int = 10) -> List[Tuple[int, int]]:
    audio = AudioSegment.from_mp3(mp3File).set_channels(1).set_frame_rate(8000)
    samples = np.array(audio.get_array_of_samples(), dtype=np.float32)  

    stepSize = int(audio.frame_rate * (stepMs / 1000.0))  
    output: List[Tuple[int, int]] = []

    lastFreq = None
    currentDuration = 0

    for i in range(0, len(samples), stepSize):
        chunk = samples[i:i + stepSize]
        if len(chunk) < stepSize:
            break  

        window = np.hanning(len(chunk))
        fftResult = np.abs(scipy.fftpack.fft(chunk * window))
        freqs = scipy.fftpack.fftfreq(len(chunk), d=1/audio.frame_rate)

        peakIdx = np.argmax(fftResult[:len(fftResult)//2])
        peakFreq = int(freqs[peakIdx])

        if peakFreq < 20 or peakFreq > 5000:
            continue  

        if lastFreq is not None and abs(peakFreq - lastFreq) <= tolerance:
            currentDuration += stepMs  
        else:
            if lastFreq is not None:
                output.append((lastFreq, currentDuration))  
            lastFreq = peakFreq
            currentDuration = stepMs  

    if lastFreq is not None:
        output.append((lastFreq, currentDuration))

    return output

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("usage: scripts/MP3toSpeaker.py <fileName.mp3>")
        exit(1)

    data = mp3ToSpeaker(sys.argv[1])
    total_time_converted = sum(d[1] for d in data) / 1000.0  
    total_time_original = AudioSegment.from_mp3(sys.argv[1]).duration_seconds  

    print(f"Original audio length: {total_time_original:.2f} sec")
    print(f"Converted audio length: {total_time_converted:.2f} sec")

    for freq, duration in data:
        print(f"speaker({freq}, {duration});")
