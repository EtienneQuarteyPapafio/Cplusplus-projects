%Tapetest with filter
%combined feedforward feedback

clear;clc;

[in,Fs]=audioread('AcGtr.wav'); %reads file into array and gets length

Ts=1/Fs; %gets sampling rate and converts to seconds

N = length(in); %total number of samples

t=(0:N-1)*Ts; 

t=t(:);


nyq=Fs/2; %nyquist

FreqHz=18000; % frequency in Hz for cut off

Wn=FreqHz/nyq; % normalised 1

[antialias]=butter(2,Wn,"low"); %2 order


timeMs=600; %delay times in millisecs

timeSec=timeMs/1000;%convert into secs

timeSamples=fix(timeSec*Fs); % delay time convertered into samples

buffer = zeros(timeSamples,1); %create new buffer

g=0.5; %mix of delay

a=0.25; %gain for delay

in2=in;

in2=conv(in2,antialias)*a; %applies filter to delayed line

delayed=zeros(N+timeSamples,1);

out=zeros(N+timeSamples,1);


for n = 1:N

%to avoid indexing a negative sample number

if n<timeSamples+1


    delayed(n,1)=0;

    %does not add to current signal preventing doubling

else

delayed(n,1)=in2(n-timeSamples,1);

%creates a delayed line


end

end



for n = 1:N

    if n<timeSamples+1
    
    %prevents doubling

    out(n,1)=0;

else

out(n,1)= (in(n,1)*(1-g))+(delayed(n,1)*g); 

    end

end


% Plot the output signal

%hold on;
%plot(t, in, '--r');
%plot(t, delayed(1:N), ':b');
%plot(t, out(1:N),'.g');  % Plot only the first N samples of 'out'
%hold off;
%xlabel('Time (seconds)');
%ylabel('Amplitude');
%title('Dry Vs Wet Signal 60ms');
%legend('Dry', ' Wet');


%freqz(in);
%freqz(in2);

sound(out,Fs);

filename = 'AcGtrEffected.wav';
audiowrite(filename,out,Fs);