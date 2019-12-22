enum RoundingMode 
{
	nearest;
	discardFractional;
	floor;
	none;
    #if cpp
		float32;
	#end
}

/** Planetside2 base capture timer case study
 * 
 * @author Paletz
 */
class Test 
{
	static var ticksPerSecond = 60;
	static var maxServerOverload = 0.35;
	static var fullCaptureProgress = 130000;
	static var fullCaptureTimeS = 5 * 60;
	static var roundingMode =  RoundingMode.nearest;
	
	static var reportFrequencyS = 30;
	
	static var fullCaptureTimeMs : Float = fullCaptureTimeS * 1000;
	static var fullCaptureTimeTicks : Int = fullCaptureTimeS * ticksPerSecond;
	
	static var idealTickDurationMs : Float = 1000.0 / ticksPerSecond;
	static var progressPerIdealTick : Float =  fullCaptureProgress / fullCaptureTimeTicks;
	
	var captureProgress : Float = 0;
	var currentTimeMs : Float = 0.0;
	var lastReportTimeMs : Float = 0.0;
	var previousTickDurationMs : Float = idealTickDurationMs;

	
	static function main() 
	{
		new Test().run();
	}

	function new()
	{
	}

	function run()
	{
		reportProgress();
		
		do
		{
			tick();
		}
		while ( captureProgress < fullCaptureProgress );
		
		reportProgress();
		
		trace( 'static var ticksPerSecond = $ticksPerSecond;' );
		trace( 'static var maxServerOverload = $maxServerOverload;' );
		trace( 'static var fullCaptureProgress = $fullCaptureProgress;' );
		trace( 'static var fullCaptureTimeS = $fullCaptureTimeS;' );
		trace( 'static var roundingMode =  RoundingMode.$roundingMode;' );
		trace( "\"Ideal\" capture progress per tick: " + progressPerIdealTick );
		trace( "Average capture progress per tick: " + computeCaptureProgressForTick(idealTickDurationMs * (1.0 + maxServerOverload / 2)) );
		trace( "Maximum capture progress per tick: " + computeCaptureProgressForTick(idealTickDurationMs * (1.0 + maxServerOverload)) );
		trace( 'Max server overload: ${maxServerOverload*100}%');
	    trace( "Average ticks per second: " + 1 / ((1 / ticksPerSecond) * (1 + maxServerOverload / 2)) );
	}
	
	function tick()
	{
		if ( lastReportTimeMs + reportFrequencyS*1000 <= currentTimeMs ) 
		{
			reportProgress();
			lastReportTimeMs = lastReportTimeMs + reportFrequencyS*1000;
		}
		captureProgress = computeUpdatedCaptureProgress();
		updateTime();
	}
	
	function updateTime()
	{
		previousTickDurationMs = idealTickDurationMs + (idealTickDurationMs * maxServerOverload * Math.random());
		currentTimeMs += previousTickDurationMs;
	}
	
	
	
	function computeUpdatedCaptureProgress() : Float
	{
		return round( captureProgress + round( computeCaptureProgressForTick( previousTickDurationMs ) ) );
	}
	
	function computeCaptureProgressForTick( tickDurationMs : Float ) : Float
	{
		return progressPerIdealTick * (tickDurationMs / idealTickDurationMs);
	}
	
	function round( value : Float ) : Float
	{
		switch ( roundingMode )
		{
			case floor:
				return Math.floor( value );
			case discardFractional:
				if ( value >= 0 ) return Math.floor( value );
				else              return Math.ceil( value );
			case nearest:
				return Math.round( value );
			case none:
				return value;
			#if cpp
			case float32:			
				return cast( value, cpp.Float32 );
			#end

		}
	}
		
	
	
	function reportProgress()
	{
		trace(
			'Time:  ${formatTimestamp( currentTimeMs )}, ' +
			'ETC:   ${formatTimestamp( estimateTimeTillCaptureMs() )}, ' +
			'Delay: ${formatTimestamp( (estimateTimeTillCaptureMs()+currentTimeMs) - fullCaptureTimeMs )}. ' +
			'Progress for prev tick: ${computeUpdatedCaptureProgress() - captureProgress}' 
		);
	}
	
	function estimateTimeTillCaptureMs()
	{
		return fullCaptureTimeMs * ( (fullCaptureProgress - captureProgress) / fullCaptureProgress );
	}
	
	function formatTimestamp( timestampMs : Float )
	{
		if ( -0.001 < timestampMs && timestampMs < 0 )
		{
			timestampMs = 0; // avoid -0:000
		}
		
		var seconds = (
			if ( timestampMs >= 0 ) StringTools.lpad( "" + Math.floor( timestampMs / 1000 ), " ", 3 )
			else                    StringTools.lpad( "-" + Math.floor(  Math.abs(timestampMs / 1000 ) ), " ", 3 )
		);
				
		return (
			seconds
			+ ":"
		    + StringTools.lpad( "" + Math.floor( Math.abs( timestampMs % 1000 ) ), "0", 3 )
		);
	}
}

/** This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org/>
 */