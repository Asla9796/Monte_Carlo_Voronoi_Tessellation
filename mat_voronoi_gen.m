#!/usr/bin/octave -qf

x = gallery('uniformdata',[1000 2], 4);
[v,c] = voronoin(x); 
for i = 1:length(c) 
if all(c{i}~=1)   % If at least one of the indices is 1, 
                  % then it is an open region and we can't 
                  % patch that.
patch(v(c{i},1),v(c{i},2),i); % use color i.
end
end