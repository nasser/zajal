#import "NSString+UniquePaths.h"

@implementation NSString (UniquePaths)

+(NSString*) uniquePathFromPath:(NSString*)path {
    // TODO, expand beyond letters into double letters (aa, ab, ac etc)
    // http://stackoverflow.com/questions/3549060/concatenate-one-nsmutablearray-to-the-end-of-another-nsmutablearray
    NSArray* alphabet = [NSArray arrayWithObjects:
                        @"a", @"b", @"c", @"d", @"e", @"f", @"g", @"h", @"i", @"j", @"k", @"l", @"m", @"n", 
                        @"o", @"p", @"q", @"r", @"s", @"t", @"u", @"v", @"w", @"x", @"y", @"z", nil];
    
    NSString* suffix = [path pathExtension];
    NSInteger suffixIndex = [path length] - [suffix length];
    NSString* pathWithoutSuffix;
    
    if([suffix length] > 0) {
        suffixIndex -= 1;
        pathWithoutSuffix = [path substringToIndex:suffixIndex];
    } else {
        pathWithoutSuffix = path;
    }
    
    NSString* dateAbrev = [[NSDate date] descriptionWithCalendarFormat:@"%b%d" timeZone:nil locale:nil];
    
    for(NSString* letter in alphabet) {
        NSString* uniqueFileName = [[NSString stringWithFormat:@"%@_%@%@.%@", pathWithoutSuffix, dateAbrev, letter, suffix] lowercaseString];
        
        if(![[NSFileManager defaultManager] fileExistsAtPath:uniqueFileName]) {
            return  uniqueFileName;
        }
    }
    
    return nil;
}

@end
