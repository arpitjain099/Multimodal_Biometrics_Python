%------------------------------------------------------------------------
%pseudo_matched_filter
%Implements root filtering technique to increase SNR of an image
%usage:
%y = pseudo_matched_filter(x,alpha)
%y -  [OUT] enhanced image
%x - [IN] input image
%alpha - [IN] exponent to which the FFT mag is raised. having larger alpha
%        will increase smoothness, but will also introduce artefacts. 
%        optimal - 0.5 to 1
%Contact:
%   ssc5@eng.buffalo.edu
%   www.eng.buffalo.edu/~ssc5
%------------------------------------------------------------------------
function y = pseudo_matched_filter(x,alpha)
    [h,w]   =   size(x);
    x       =   double(x);
    f       =   fft2(x);
    f       =   (abs(f).^alpha).*f; %this is all root filtering is about
    y       =   real(ifft2(f));
%end function pseudo_matched_filter