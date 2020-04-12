% 16 samples/bit.  Find index of start bit rise, sample 8 bits in and every
% 16 samples thereafter.  This is finalData
% Have 32*30 0's, but this is 16*30 in my sampling

myfile = fopen('cards.txt','a');




clf
rawdata = sample1;  
datamean = mean(rawdata);
for i = 1:length(rawdata)
    if(rawdata(i)>datamean)
        rawdata(i) = 0;
    else
        rawdata(i) = 1;
    end
end
plot(rawdata);
ylim([-1,2]);
startBits = findStartBit(rawdata);
xticks(startBits);

% Center start bits:
startBits = startBits + 8;

%sample into a matrix.
bitsArray = zeros(length(startBits),224);
for i = 1:(length(startBits)-1)
    for j = 1:224
        bitsArray(i,j) = rawdata(startBits(i)+16*(j-1));
    end    
end

for k = 1:33
    fprintf(myfile,'%2d',bitsArray(1,22+k));
end
fprintf(myfile,'\n');
fclose(myfile);


%find string of 0's.  Technically there should be 16*30, but this provides some room for error.
function startBitIndex = findStartBit(binaryData)
startBitIndex = [];
for i = (1+15*30):length(binaryData)
    if(sum(binaryData((i-15*30):i-1))==0)
        if(binaryData(i) == 1)
            startBitIndex = [startBitIndex,i];
        end
    end
end
end

